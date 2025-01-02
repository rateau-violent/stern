#ifndef BACKEND_SERVER_H
#define BACKEND_SERVER_H

#include "concepts.h"
#include "module_base.h"

#include <iostream>

namespace backend {
    template <Framework F, typename Route>
    class server {
        using module_type = backend::module_base<F, Route>;

        using request_type = typename F::request_type;
        using response_type = typename F::response_type;
        using method_type = typename F::method_type;

        public:
            explicit server(std::size_t port, module_type&& main_module): _port{port}, _main_module{std::move(main_module)} {

            }

            void start() {
                // temporary implementation
                std::cout << "===============" << std::endl;
                std::cout << "STARTING SERVER" << std::endl;
                std::cout << "===============" << std::endl;

                std::cout << "PORT=" << _port << std::endl;
                srand(time(nullptr));
                sleep(2);
                std::cout << "Done!" << std::endl;
                _run();
            }
        private:
            std::size_t _port;
            module_type _main_module;

            void _run() {
                std::cout << "=================" << std::endl;
                std::cout << "SERVER IS RUNNING" << std::endl;
                std::cout << "=================" << std::endl;

                for (std::size_t i = 0; i < 15; ++i) {
                    try {
                        sleep(1);
                        auto req = _get_request();

                        std::cout << "RECEIVED REQUEST: " << std::to_string(req.method) << " " << req.path << std::endl;

                        auto res = _main_module(req);

                        if (res == std::nullopt) {
                            std::cout << "404 Not found" << std::endl;
                        } else {
                            std::cout << "OK" << std::endl;
                        }
                        std::cout << "----------" << std::endl;
                    } catch (const std::exception& e) {
                        std::cerr << "ERROR: " << e.what() << std::endl;
                    }
                }
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
    };
}

#endif /* !BACKEND_SERVER_H */
