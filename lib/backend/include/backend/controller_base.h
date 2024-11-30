#ifndef BACKEND_CONTROLLER_BASE_H
#define BACKEND_CONTROLLER_BASE_H

#include <string>
#include <unordered_map>
#include <optional>
#include <concepts>

namespace backend {

    template<typename T>
    concept Module = requires(T t) {
        typename T::request_type;
        typename T::response_type;
        typename T::method_type;

        T::request_type::path;
        T::request_type::method;
    };

    template<typename T, typename Req, typename Res>
    concept Callable = requires(T t, Req req) {
        t(req) -> Res;
    };

    template <Module M, typename Route>
    class controller_base {
        using request_type = typename M::request_type;
        using response_type = typename M::response_type;
        using method_type = typename M::method_type;

        using route_tuple = std::tuple<std::string, method_type, Route>;

        public:
            explicit controller_base(const std::string& prefix = ""): _prefix{prefix} {
            }

            virtual ~controller_base() = default;

            [[nodiscard]]
            std::optional<response_type> operator()(const request_type& req) {
                auto r = _routes.find({req.path, req.method});

                if (r == _routes.end()) {
                    return std::nullopt;
                }

                return r->second(req);
            }

            void emplace_routes(std::initializer_list<route_tuple> routes) {
                for (auto r: routes) {
                    _routes.emplace(route_key{_prefix + std::get<0>(r), std::get<1>(r)}, std::get<2>(r));
                }
            }

        private:
        struct route_key {
            std::string path;
            method_type method;

            bool operator==(const route_key&other) const {
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

        std::string _prefix;
        std::unordered_map<route_key, Route, route_key_hash> _routes;
    };
}

#endif /* !BACKEND_CONTROLLER_BASE_H */
