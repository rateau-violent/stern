#ifndef HTTP_BODY_H
#define HTTP_BODY_H

#include <string>
#include <variant>

#include <nlohmann/json.hpp>

namespace http {

    class body_type {
        public:
            using json = nlohmann::json;

            explicit body_type() = default;
            explicit body_type(const std::string& content);
            explicit body_type(std::string&& content);
            explicit body_type(const char* content);
            explicit body_type(const json& content);
            explicit body_type(json&& content);

            body_type& operator=(const body_type&) = default;

            bool operator==(const body_type&) const = default;

            std::size_t size() const noexcept;

            std::string to_string() const;

            bool is_json() const;

        private:
            std::variant<std::string, json> _data;
    };
}

#endif /* !HTTP_BODY_H */
