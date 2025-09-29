#ifndef STERN_PARAMETERS_H
#define STERN_PARAMETERS_H

#include <rfl.hpp>
#include <rfl/json.hpp>

#include "framework.h"

namespace stern::parameter {
    struct query{};

    struct body{};

    struct uri{};

    template<typename T>
    concept QueryParameter = std::is_base_of_v<query, T>;

    template<typename T>
    concept BodyParameter = std::is_base_of_v<body, T>;

    template<typename T>
    concept UriParameter = std::is_base_of_v<uri, T>;

    template<typename T>
    concept RouteParameter = QueryParameter<T> || BodyParameter<T> || UriParameter<T>;

    template<Framework F>
    struct transformer {
        using request_type = typename F::request_type;

        template<QueryParameter P>
        static P transform(const request_type& req) {
            return rfl::json::read<P>(F::query_to_json(req)).value();
        }

        template<BodyParameter P>
        static P transform(const request_type& req) {
            return rfl::json::read<P>(F::body_to_json(req)).value();
        }

        template<UriParameter P>
        static P transform(const request_type& req) {
            return rfl::json::read<P>(F::uri_to_json(req)).value();
        }
    };

}

#endif /* !STERN_PARAMETERS_H */
