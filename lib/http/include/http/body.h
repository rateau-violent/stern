#ifndef HTTP_BODY_H
#define HTTP_BODY_H

#include <string>
#include <variant>

#include <nlohmann/json.hpp>

namespace http {

    class body_type {
        using json = nlohmann::json;
        public:
            body_type(const std::string& content);
            body_type(std::string&& content);
            body_type(const char* content);
            body_type(const json& content);
            body_type(json&& content);

            std::size_t size() const noexcept;

            std::string to_string() const;

            bool is_json() const;

        private:
            std::variant<std::string, json> _data;
    };
}

#endif /* !HTTP_BODY_H */
