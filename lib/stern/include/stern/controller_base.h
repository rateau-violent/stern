#ifndef STERN_CONTROLLER_BASE_H
#define STERN_CONTROLLER_BASE_H

#include <string>
#include <unordered_map>
#include <optional>
#include <typeindex>
// #include <utils.h>

#include "framework.h"
#include "parameters.h"

namespace stern {
    /**
     * @brief A controller defines and contains routes for a part of the backend (e.g. user management)
     * Each of the controllers can inherit from the controller_base class or can be declared directly as a controller_base
     * A controller_base handles all the routes it contains and calls the right route for the given method and path
     * @tparam F The framework used by the controller
     */
    template <Framework F>
    class controller_base {

        using request_type = typename F::request_type;
        using response_type = typename F::response_type;
        using method_type = typename F::method_type;

        public:
            using route_type = std::function<response_type (const request_type&)>;
        private:
            using route_tuple = std::tuple<std::string, method_type, route_type>;

        public:
            struct route_key {
                std::string path;
                method_type method;

                bool operator==(const route_key& other) const {
                    return path == other.path && method == other.method;
                }
            };

            struct route_key_hash {
                std::size_t operator()(route_key key) const {
                    std::size_t h1 = std::hash<std::string>{}(key.path);
                    std::size_t h2 = std::hash<method_type>{}(key.method);

                    return h1 ^ (h2 << 1);
                }
            };

            /**
             * @brief Constructs a controller_base object
             * @param [in] prefix An optional prefix that will be applied to all the controller's routes path
             */
            explicit controller_base(const std::string& prefix = ""): _prefix{prefix} {
            }

            controller_base(const controller_base &other) = default;
            controller_base(controller_base &&other) = default;

            controller_base& operator=(const controller_base&) = default;
            controller_base& operator=(controller_base&&) = default;

            virtual ~controller_base() = default;

            /**
             * @brief Tries to call the right route for the request's method and path
             * @param [in] req A request object
             * @return Either a response object or std::nullopt if the route is not found in the controller
             */
            [[nodiscard]]
            std::optional<response_type> operator()(const request_type& req) {
                auto r = _routes.find({req.path, req.method});

                if (r == _routes.end()) {
                    return std::nullopt;
                }

                return r->second(req);
            }

            /**
             * @brief Adds the given routes to the controller
             * @param [in] routes A list of routes to handle
             */
            void emplace_routes(std::initializer_list<route_tuple> routes) {
                for (auto r: routes) {
                    _routes.emplace(route_key{_prefix + std::get<0>(r), std::get<1>(r)}, std::get<2>(r));
                }
            }

            template<parameter::RouteParameter... Params, typename Function>
            controller_base& emplace_route(const std::string& path, method_type m, Function f) {
                static_assert(sizeof ...(Params) < 4);

                _routes.emplace(route_key{_prefix + path, m}, [f = std::forward<Function>(f)](const request_type& r) {
                    return f(r, parameter::transformer<F>::template transform<Params>(r)...);
                });
                return *this;
            }

            const std::unordered_map<route_key, route_type, route_key_hash>& get_routes() const noexcept {
                return _routes;
            }

        private:
            std::string _prefix;
            std::unordered_map<route_key, route_type, route_key_hash> _routes;
    };
}

#endif /* !STERN_CONTROLLER_BASE_H */
