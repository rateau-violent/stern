#ifndef HTTP_QUERY_H
#define HTTP_QUERY_H
#include <nlohmann/json.hpp>

namespace http {

class query_type {
    public:
        using json = nlohmann::json;

        /**
         * @brief Constructs an empty query object
         */
        explicit query_type() = default;

        /**
         * @brief Constructs a query object from a string
         * @param [in] content The query string, extracted from the request's uri
         */
        explicit query_type(const std::string& content);

        /**
         * @brief returns the query as a json object
         */
        [[nodiscard]] std::string to_string() const;

        /**
         * @brief Returns true if the query is empty, false otherwise
         */
        [[nodiscard]] bool empty() const;

    private:
        json _data{};

};
}

#endif /* !HTTP_QUERY_H */
