#ifndef STERN_PARAMETERS_H
#define STERN_PARAMETERS_H

#include <rfl.hpp>
#include <rfl/json.hpp>

#include "stern/framework.h"

namespace stern::parameter {

    /**
     * @brief Defines a query parameter
     */
    struct query{};

    /**
     * @brief Defines a body parameter
     */
    struct body{};

    /**
     * @brief Defines an uri parameter
     */
    struct uri{};

    /**
     * @brief Concept for query parameters
     */
    template<typename T>
    concept QueryParameter = std::is_base_of_v<query, T>;

    /**
     * @brief Concept for body parameters
     */
    template<typename T>
    concept BodyParameter = std::is_base_of_v<body, T>;

    /**
     * @brief Concept for uri parameters
     */
    template<typename T>
    concept UriParameter = std::is_base_of_v<uri, T>;

    /**
     * @brief Concept for route parameters
     */
    template<typename T>
    concept RouteParameter = QueryParameter<T> || BodyParameter<T> || UriParameter<T>;

    /**
     * @brief Transforms any Route parameter (query parameter, body parameter or uri parameter) into a representative
     * structure
     */
    template<Framework F>
    struct transformer {
        using request_type = typename F::request_type;

        /**
         * @brief Transforms a query parameter into a representative structure
         */
        template<QueryParameter P>
        static P transform(const request_type& req) {
            try {
                return rfl::json::read<P>(F::query_to_json(req)).value();
            } catch (...) {
                F::on_ill_formed_request(req);
                return P{};
            }
        }

        /**
         * @brief Transforms a body parameter into a representative structure
         */
        template<BodyParameter P>
        static P transform(const request_type& req) {
            try {
                return rfl::json::read<P>(F::body_to_json(req)).value();
            } catch (...) {
                F::on_ill_formed_request(req);
                return P{};
            }
        }

        /**
         * @brief Transforms an uri parameter into a representative structure
         */
        template<UriParameter P>
        static P transform(const request_type& req) {
            try {
                return rfl::json::read<P>(F::uri_to_json(req)).value();
            } catch (...) {
                F::on_ill_formed_request(req);
                return P{};
            }
        }
    };

}

#endif /* !STERN_PARAMETERS_H */
