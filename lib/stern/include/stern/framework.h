#ifndef STERN_FRAMEWORK_H
#define STERN_FRAMEWORK_H

#include <concepts>

namespace stern {
    /**
     * @brief Defines the types required by the backend module
     */
    template<typename T>
    concept Framework = requires(T t) {
		/// defines the framework's request type
        typename T::request_type;
		/// defines the framework's response type
        typename T::response_type;
		/// defines the framework's HTTP method type
        typename T::method_type;

		/// the framework request_type must have a member variable named path, that must be a string
        T::request_type::path;
        std::same_as<decltype(std::declval<typename T::request_type>().path), std::string>;
		/// the framework's request type must be constructible from a string
        std::is_constructible_v<typename T::request_type, std::string>;

		/// the framework's request type must have a member named method, that must be the same type as the previously
		/// declared framework's method_type
        T::request_type::method;
        std::same_as<decltype(std::declval<typename T::request_type>().method), typename T::method_type>;

		/// the framework must implement a function that returns the request's body as a json string
		{ T::body_to_json(typename T::request_type("")) } -> std::same_as<std::string>;
    	/// the framework must implement a function that returns the request's query parameters as a json string
    	{ T::query_to_json(typename T::request_type("")) } -> std::same_as<std::string>;
		/// the framework must implement a function that returns the request's uri parameters as a json string
    	{ T::uri_to_json(typename T::request_type("")) } -> std::same_as<std::string>;

    	/// the framework must implement a function to handle not found routes
    	{ T::not_found(typename T::request_type("")) } -> std::same_as<typename T::response_type>;
    	/// the framework must implement a function to handle caught exceptions
	    { T::on_exception(typename T::request_type(""), std::exception()) } -> std::same_as<typename T::response_type>;
    	/// the framework must implement a function to handle caught unknown exceptions
	    { T::on_unknown_exception(typename T::request_type("")) } -> std::same_as<typename T::response_type>;
    };
}

#endif /* !STERN_FRAMEWORK_H */
