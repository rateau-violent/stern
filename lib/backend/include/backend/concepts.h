#ifndef BACKEND_CONCEPTS_H
#define BACKEND_CONCEPTS_H

#include <concepts>

namespace backend {
    template<typename T>
    concept Framework = requires(T t) {
        typename T::request_type;
        typename T::response_type;
        typename T::method_type;

        T::request_type::path;
        std::same_as<decltype(std::declval<typename T::request_type>().path), std::string>;

        T::request_type::method;
        std::same_as<decltype(std::declval<typename T::request_type>().method), typename T::method_type>;
    };
}

#endif /* !BACKEND_CONCEPTS_H */
