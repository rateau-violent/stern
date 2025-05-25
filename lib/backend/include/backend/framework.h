#ifndef BACKEND_CONCEPTS_H
#define BACKEND_CONCEPTS_H

#include <concepts>

namespace backend {
    /**
     * @brief Defines the types required by the backend module
     */
    template<typename T>
    concept Framework = requires(T t) {
		// defines the framework's request type
        typename T::request_type;
		// defines the framework's response type
        typename T::response_type;
		// defines the framework's HTTP method type
        typename T::method_type;

		// the framework request_type must have a member variable named path, that must be a string
        T::request_type::path;
        std::same_as<decltype(std::declval<typename T::request_type>().path), std::string>;
		// the framework's request type must be constructible from a string
        std::is_constructible_v<typename T::request_type, std::string>;

		// the framework's request type must have a member named method, that must be the same type as the previously
		// declared framework's method_type
        T::request_type::method;
        std::same_as<decltype(std::declval<typename T::request_type>().method), typename T::method_type>;

		// the framework must implement a function that returns the request's body as a json string
		{ T::body_to_json(typename T::request_type("")) } -> std::same_as<std::string>;
    };
}

#endif /* !BACKEND_CONCEPTS_H */
