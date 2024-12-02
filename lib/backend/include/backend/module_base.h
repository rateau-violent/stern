#ifndef BACKEND_MODULE_H
#define BACKEND_MODULE_H

#include <vector>
#include <memory>

#include <iostream>

#include "controller_base.h"

namespace backend {
template<Framework F, typename Route>
class module_base {
    using request_type = typename F::request_type;
    using response_type = typename F::response_type;
    using method_type = typename F::method_type;


    public:
        explicit module_base(): _controllers{}, _submodules{} {
        };

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
