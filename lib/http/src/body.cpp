#include "http/body.h"

namespace http {
    body_type::body_type(const std::string& content) {
        try {
            auto json_content = json::parse(content);

            _data = json_content;
        } catch (...) {
            _data = content;
        }

    }
    body_type::body_type(const char* content): body_type(std::string(content)) {}
    body_type::body_type(const json& content): _data{content} {}

    body_type::body_type(std::string&& content): _data{std::move(content)} {}
    body_type::body_type(json&& content): _data{std::move(content)} {}


    std::size_t body_type::size() const noexcept {
        struct visitor {
            std::size_t operator()(const std::string& s) const { return s.size(); }
            std::size_t operator()(const json& o) const { return nlohmann::to_string(o).size(); }
        };

        return std::visit(visitor{}, _data);
    }

    std::string body_type::to_string() const {
        struct visitor {
            std::string operator()(const std::string& s) const { return s; }
            std::string operator()(const json& o) const { return nlohmann::to_string(o); }
        };

        return std::visit(visitor{}, _data);
    }

    bool body_type::is_json() const {
        struct visitor {
            bool operator()(const std::string& s) const { return false; }
            bool operator()(const json& o) const { return true; }
        };

        return std::visit(visitor{}, _data);
    }

}
