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
                _tcp_server{port} {
            }

            void start() {
                std::cout << "===============" << std::endl;
                std::cout << "STARTING SERVER" << std::endl;
                std::cout << "===============" << std::endl;
                std::cout << "PORT=" << _port << std::endl;
                signal(SIGINT, server::signal_handler);

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

            std::atomic<std::queue<request_type>> _requests;

            static inline bool _running = true;

            void _run() {
                std::cout << "=================" << std::endl << "SERVER IS RUNNING" << std::endl << "=================" << std::endl;

                while (_running) {
                    if (!_requests.empty()) {
                        auto request = _requests.front();

                        _requests.pop_front();
                    } else {
                        std::this_thread::yield();
                    }
                }

                stop();
            }

            request_type _get_request() {
                // temporary implementation
                static const std::vector<http::request> requests{
                    {"/users", http::methods::POST },
                    {"/users", http::methods::PUT },
                    {"/users", http::methods::GET },
                    {"/users", http::methods::DELETE },
                    {"/", http::methods::GET },
                    {"/", http::methods::POST }
                };
                std::size_t req = std::rand() % requests.size();

                return requests[req];
            }

            static void signal_handler(int) {
                _running = false;
            }
    };
}

#endif /* !BACKEND_SERVER_H */
