#include <sstream>
#include <iostream>

#include "http/response.h"

namespace http {
    response::response(codes c, const std::string& b): code{c}, body(b) {
        headers.emplace("Content-Length", std::to_string(body.size() + 2));
        headers.emplace("Content-Type", "text/html; charset=UTF-8");
    }

    response::response(const error::error& e) noexcept: response(e.code, e.message) {}

    response::operator std::string() const {

        if (!version) {
            throw std::runtime_error("HTTP version not defined in response");
        }

        std::stringstream ss;
        ss << std::to_string(*version) << " " << std::to_string(static_cast<uint16_t>(code)) << " " << std::to_string(code) << "\n\r";
        for (const auto& [key, value]: headers) {
            ss << key << ": " << value << "\r\n";
        }
        ss << "\r\n" << body << "\r\n";
        return ss.str();
    }

    response& response::complete(const request& req) {
        version = req.version;
        return *this;
    };
}