#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <optional>

#include "body.h"
#include "error.h"
#include "versions.h"
#include "request.h"

namespace http {
    class response {
    public:
        explicit response(codes code, const body_type& body);
        explicit response(codes c, const std::string& b);
        response(const response& res) noexcept = default;
        response(response&& res) noexcept = default;
        explicit response(const error::error& e) noexcept;

        explicit operator std::string() const;

        response& complete(const request& req);

        /**
         * Returns the response's code
         */
        [[nodiscard]] codes getCode() const;

        /**
         * Returns the response's body
         */
        [[nodiscard]] const body_type& getBody() const;

        private:
            codes code;
            body_type body;
            std::optional<versions> version{std::nullopt};
            std::unordered_map<std::string, std::string> headers;
    };

}

#endif /* !HTTP_RESPONSE_H */
