#ifndef STERN_MODULE_H
#define STERN_MODULE_H

#include <vector>
#include <memory>

#include <iostream>

#include "controller_base.h"

namespace stern {
    /**
     * @brief A module contains and handle multiple controller and/or multiple submodules
     * Each of the modules must inherit from the module_base class
     * A module_base handles all the routes from the contained controllers and submodules for the given module and path
     * @tparam F The framework used by the module
     */
    template<Framework F>
    class module_base {
        using request_type = typename F::request_type;
        using response_type = typename F::response_type;
        using method_type = typename F::method_type;

        using controller_type = controller_base<F>;
        using route_type = typename controller_type::route_type;

        public:
            /**
             * @brief Constructs a module_base object
             */
            explicit module_base(): _controllers{}, _submodules{} {
            };

            /**
             * @brief Tries to call the right route for the request's method and path
             * @param [in] request A request object
             * @return Either a response or std::nullopt if the route is not found on the module's controllers or submodules
             */
            std::optional<response_type> operator()(const request_type& request) {
                for (auto& c_ptr: _controllers) {
                    if (auto res = (*c_ptr)(request); res != std::nullopt) {
                        return (*res);
                    }
                }

                for (auto& m_ptr: _submodules) {
                    if (auto res = (*m_ptr)(request); res != std::nullopt) {
                        return (*res);
                    }
                }
                return std::nullopt;
            }

            const std::unordered_map<typename controller_type::route_key, route_type, typename controller_type::route_key_hash>&
                get_routes() const noexcept {
                return _routes;
            }

        protected:
            template<typename ControllerType, typename... P>
            void _emplace_controller(P... params) {
                // _emplace_routes(_controllers, params...);
                _controllers.emplace_back(std::make_unique<ControllerType>(params...));

                for (const auto& c: _controllers) {
                    for (const auto& r: c->get_routes()) {
                        _routes.emplace(r);
                    }
                }
            }

            template<typename ModuleType, typename... P>
            void _emplace_submodule(P... params) {
                // _emplace_routes(_submodules, params...);
                _submodules.emplace_back(std::make_unique<ModuleType>(params...));

                for (const auto& m: _submodules) {
                    for (const auto& r: m->get_routes()) {
                        _routes.emplace(r);
                    }
                }
            }

        private:
            std::vector<std::unique_ptr<controller_type>> _controllers;
            std::vector<std::unique_ptr<module_base<F>>> _submodules;
            std::unordered_map<typename controller_type::route_key, route_type, typename controller_type::route_key_hash> _routes;

            // template<typename T, typename... P>
            // void _emplace_routes(std::vector<std::unique_ptr<T>>& container, P... params) {
            //     auto size = container.size();
            //
            //     std::cout << "size = " << size << std::endl;
            //     container.emplace_back(std::make_unique<T>(params...));
            //
            //     std::cout << "new size = " << container.size() << std::endl;
            //     for (std::size_t i = size; i < container.size(); ++i) {
            //         std::cout << "coucou " << i << std::endl;
            //         std::cout << container[i]->get_routes().size() << std::endl;
            //         for(const auto& r: container[i]->get_routes()) {
            //             std::cout << "salut" << std::endl;
            //             _routes.emplace(r);
            //         }
            //     }
            // }

    };
}

# endif /* !STERN_MODULE_H */
