#ifndef STERN_SERVER_H
#define STERN_SERVER_H

#include "framework.h"
#include "module_base.h"

#include <iostream>
#include <thread>
#include <csignal>
#include <queue>

#include <network/tcp_server.h>

namespace stern {
    template <Framework F>
    class server {
        using module_type = module_base<F>;
        using controller_type = controller_base<F>;
        using route_type = typename controller_type::route_type;

        using request_type = typename F::request_type;
        using response_type = typename F::response_type;
        using method_type = typename F::method_type;

        public:
            explicit server(std::size_t port, module_type&& main_module):
                _port{port},
                _main_module{std::move(main_module)},
                _routes{_main_module.get_routes()},
                _tcp_server{port, [this](const std::shared_ptr<network::tcp_connection>& c, const std::string& data) {
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

            void stop() {
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

            void _request_handler(const std::shared_ptr<network::tcp_connection>& c, const std::string& data) noexcept {
                request_type req(data);

                try {
                    if (auto res = _get_response(req); res) {
                        c->send(res.value().complete(req));
                    } else {
                        c->send(http::response{http::error::not_found{}}.complete(req));
                    }
                } catch (const http::error::error& e) {
                    c->send(http::response{e}.complete(req));
                } catch (const std::exception& e) {
                    std::cerr << "ERROR: " << e.what() << std::endl;
                    c->send(http::response{http::error::internal_server_error{}}.complete(req));
                } catch (...) {
                    std::cerr << "ERROR: Unknown error" << std::endl;
                    c->send(http::response{http::error::internal_server_error{}}.complete(req));
                }
            }

            static void _signal_handler(int) {
                _running = false;
            }
    };
}

#endif /* !STERN_SERVER_H */
