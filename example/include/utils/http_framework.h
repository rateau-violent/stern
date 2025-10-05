#ifndef EXAMPLE_UTILS_HTTP_FRAMEWORK_H
#define EXAMPLE_UTILS_HTTP_FRAMEWORK_H

#include <functional>
#include <memory>

#include <http/methods.h>
#include <http/response.h>
#include <http/request.h>

#include <stern/controller_base.h>
#include <stern/module_base.h>

namespace example {
    struct http_framework {
        using method_type = http::methods;
        using response_type = http::response;
        using request_type = http::request;

        static std::string body_to_json(const request_type& req) {
            return req.body.to_string();
        }

        static std::string query_to_json(const request_type& req) {
            return "{}"; // TODO
        }

        static std::string uri_to_json(const request_type& req) {
            return "{}"; // TODO
        }

        static response_type not_found(const request_type& req) {
            return http::response{http::error::not_found{}}.complete(req);
        }
    };
}

#endif /* !EXAMPLE_UTILS_HTTP_FRAMEWORK_H */
