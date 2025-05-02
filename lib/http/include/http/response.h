#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <optional>

#include "error.h"
#include "versions.h"
#include "request.h"

namespace http {
    class response {
        public:
            response(codes code, const std::string& body);
            response(const response& res) noexcept = default;
            response(response&& res) noexcept = default;
            response(const error::error& e) noexcept;

            operator std::string() const;

            response& complete(const request& req);

        private:
            codes code;
            std::string body;
            std::optional<versions> version{std::nullopt};
            std::unordered_map<std::string, std::string> headers;
    };
}

#endif /* !HTTP_RESPONSE_H */
