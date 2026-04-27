#ifndef STERN_SERVER_H
#define STERN_SERVER_H

#include "stern/framework.h"
#include "stern/module_base.h"

#include <iostream>
#include <thread>
#include <csignal>
#include <queue>

#include <network/tcp_server.h>

namespace stern {
    /**
     * @brief Server that handles network and routes resolution
     * @tparam F The framework used by the server
     */
    template <Framework F>
    class server {
        using module_type = module_base<F>;
        using controller_type = controller_base<F>;
        using route_type = typename controller_type::route_type;

        using request_type = typename F::request_type;
        using response_type = typename F::response_type;
        using method_type = typename F::method_type;

        public:
            /**
             * @brief Constructs a server object
             * @param [in] port The port the server will listen on
             * @param [in] main_module The backend's main module
             */
            explicit server(std::size_t port, module_type&& main_module):
                _port{port},
                _main_module{std::move(main_module)},
                _routes{_main_module.get_routes()},
                _tcp_server{{port, { network::tcp_connection::config::read_strategy::READ_UNTIL, "\r\n\r\n"}}, [this](const std::shared_ptr<network::tcp_connection>& c, const network::packet_descriptor& data) {
                    _request_handler(c, data);
                }} {
                std::cout << "The following routes will be used:" << std::endl;
                for (const auto& [name, _]: _routes) {
                    std::cout << "  " << std::setw(7) << std::to_string(name.method) << " " << name.path << std::endl;
                }
                std::cout << std::endl;
            }

            server(const server&) = delete;
            server(server&&) = delete;

            /**
             * @brief Starts the server
             */
            void start() {
                std::cout << "===============" << std::endl;
                std::cout << "STARTING SERVER" << std::endl;
                std::cout << "===============" << std::endl;
                std::cout << "PORT=" << _port << std::endl;
                signal(SIGINT, server::_signal_handler);

                _running = true;
                _network_thread = std::thread([this] () -> void {
                    _tcp_server.start();
                });
                std::cout << "Done!" << std::endl;
                _run();
            }

            /**
             * @brief Stops the server
             */
            void stop() {
                if (_running) {
                    _running = false;
                    return;
                }
                std::cout << std::endl << "=== STOPPING SERVER ===" << std::endl;
                _tcp_server.stop();
                if (_network_thread.joinable()) {
                    _network_thread.join();
                }
                std::cout << "Done!" << std::endl;
            }

        private:
            std::size_t _port;
            module_type _main_module;
            std::unordered_map<typename controller_type::route_key, route_type, typename controller_type::route_key_hash> _routes;

            network::tcp_server _tcp_server;
            std::thread _network_thread;

            static volatile inline bool _running = true;

            void _run() {
                std::cout << "=================" << std::endl
                          << "SERVER IS RUNNING" << std::endl
                          << "=================" << std::endl;

                while (_running) {
                    std::this_thread::yield();
                }

                stop();
            }

            std::optional<response_type> _get_response(const request_type& req) {
                auto r = _routes.find({req.path, req.method});

                if (r == _routes.end()) {
                    return std::nullopt;
                }

                return std::optional{r->second(req)};
            }

            void _request_handler(const std::shared_ptr<network::tcp_connection>& c, const network::packet_descriptor& packet) noexcept {
                std::string data_str;
                data_str.assign(reinterpret_cast<char*>(packet.data), packet.size);
                request_type req(data_str);

                try {
                    if (auto res = _get_response(req); res) {
                        std::string res_str{res.value()};
                        c->send({reinterpret_cast<std::uint8_t*>(res_str.data()), res_str.size()});
                    } else {
                        std::string res_str{F::not_found(req)};
                        c->send({reinterpret_cast<std::uint8_t*>(res_str.data()), res_str.size()});
                    }
                } catch (const std::exception& e) {
                    std::string res_str{F::on_exception(req, e)};
                    c->send({reinterpret_cast<std::uint8_t*>(res_str.data()), res_str.size()});
                } catch (...) {
                    std::string res_str{F::on_unknown_exception(req)};
                    c->send({reinterpret_cast<std::uint8_t*>(res_str.data()), res_str.size()});
                }
            }

            static void _signal_handler(int) {
                _running = false;
            }
    };
}

#endif /* !STERN_SERVER_H */
