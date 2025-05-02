#ifndef BACKEND_SERVER_H
#define BACKEND_SERVER_H

#include "concepts.h"
#include "module_base.h"

#include <iostream>
#include <thread>
#include <csignal>
#include <queue>

#include <network/tcp_server.h>

namespace backend {
    template <Framework F, typename Route>
    class server {
        using module_type = backend::module_base<F, Route>;

        using request_type = typename F::request_type;
        using response_type = typename F::response_type;
        using method_type = typename F::method_type;

        public:
            explicit server(std::size_t port, module_type&& main_module):
                _port{port},
                _main_module{std::move(main_module)},
                _tcp_server{port, [this](std::shared_ptr<network::tcp_connection> c, const std::string& data) {
                    _request_handler(c, data);
                }} {
            }

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
                std::cout << "=== STOPPING SERVER ===" << std::endl;
                _tcp_server.stop();
                if (_network_thread.joinable()) {
                    _network_thread.join();
                }
                std::cout << "Done!" << std::endl;
            }

        private:
            std::size_t _port;
            module_type _main_module;
            network::tcp_server _tcp_server;
            std::thread _network_thread;

            static volatile inline bool _running = true;

            void _run() {
                std::cout << "=================" << std::endl << "SERVER IS RUNNING" << std::endl << "=================" << std::endl;

                while (_running) {
                    std::this_thread::yield();
                }

                stop();
            }

            void _request_handler(std::shared_ptr<network::tcp_connection> c, const std::string& data) noexcept {
                request_type r(data);

                try {
                    auto res = _main_module(r);

                    if (res) {
                        c->send(res.value().complete(r));
                    } else {
                        c->send(http::response{http::error::not_found{}}.complete(r));
                    }
                } catch (const http::error::error& e) {
                    c->send(http::response{e}.complete(r));
                } catch (const std::exception& e) {
                    std::cerr << "ERROR: " << e.what() << std::endl;
                    c->send(http::response{http::error::internal_server_error{}}.complete(r));
                } catch (...) {
                    std::cerr << "ERROR: Unknown error" << std::endl;
                    c->send(http::response{http::error::internal_server_error{}}.complete(r));
                }
            }

            static void _signal_handler(int) {
                _running = false;
            }
    };
}

#endif /* !BACKEND_SERVER_H */
