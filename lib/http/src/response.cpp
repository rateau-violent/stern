#include <sstream>
#include <iostream>

#include "http/response.h"
#include "http/utils/string_helper.h"

namespace http {
    response::response(codes c, const body_type& b): code{c}, body(b) {
        headers.emplace("Content-Length", std::to_string(body.size() + 2));
        headers.emplace("Content-Type", (body.is_json()) ? "application/json" : "text/html; charset=UTF-8");
    }

    response::response(codes c, const std::string& b): code{c} {
        body_type content{b};

        if (content.is_json()) {
            body = content;
        } else {
            auto headers_body = utils::split_string(b, "\r\n\r\n");

            for (const auto& header: utils::split_string(headers_body[0], "\r\n") ) {
                auto [h, v]= utils::split_string_at_first_delimiter(header, ":");
                    headers.emplace(h, utils::trim_string(v, ' '));
            }
            body = body_type(headers_body[1]);
        }

        headers.emplace("Content-Type", (body.is_json()) ? "application/json" : "text/html; charset=UTF-8");
    }

    response::response(const error::error& e) noexcept: response(e.code, body_type{e.message}) {}

    response::operator std::string() const {

        if (!version) {
            throw std::runtime_error("HTTP version not defined in response");
        }

        std::stringstream ss;
        ss << std::to_string(*version) << " " << std::to_string(static_cast<uint16_t>(code)) << " " << std::to_string(code) << "\n\r";
        for (const auto& [key, value]: headers) {
            ss << key << ": " << value << "\r\n";
        }
        ss << "\r\n" << body.to_string() << "\r\n";
        return ss.str();
    }

    response& response::complete(const request& req) {
        version = req.version;
        return *this;
    };

    codes response::getCode() const {
        return code;
    }

    const body_type& response::getBody() const {
        return body;
    }


}
