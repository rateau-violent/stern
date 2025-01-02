#ifndef BACKEND_MODULE_H
#define BACKEND_MODULE_H

#include <vector>
#include <memory>

#include <iostream>

#include "controller_base.h"

namespace backend {
    /**
     * @brief A module contains and handle multiple controller and/or multiple submodules
     * Each of the modules must inherit from the module_base class
     * A module_base handles all the routes from the contained controllers and submodules for the given module and path
     * @tparam F The framework used by the module
     * @tparam Route The type of the routes used by the module and its contained controllers and submodules
     */
    template<Framework F, typename Route>
    class module_base {
        using request_type = typename F::request_type;
        using response_type = typename F::response_type;
        using method_type = typename F::method_type;

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

        protected:
            template<typename ControllerType, typename... P>
            void _emplace_controller(P... params) {
                _controllers.emplace_back(std::make_unique<ControllerType>(params...));
            }

            template<typename ModuleType, typename... P>
            void _emplace_submodule(P... params) {
                _submodules.emplace_back(std::make_unique<ModuleType>(params...));
            }

        private:
            std::vector<std::unique_ptr<controller_base<F, Route>>> _controllers;
            std::vector<std::unique_ptr<module_base<F, Route>>> _submodules;
    };
}

# endif /* !BACKEND_MODULE_H */
