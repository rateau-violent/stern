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

        static response_type on_exception(const request_type& req, const std::exception& e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
            if (auto* http_error = dynamic_cast<const http::error::error*>(&e); http_error != nullptr) {
                return http::response{*http_error}.complete(req);
            }
            return http::response{http::error::internal_server_error{}}.complete(req);
        }

        static response_type on_unknown_exception(const request_type& req) {
            std::cerr << "ERROR: Unknown error" << std::endl;
            return http::response{http::error::internal_server_error{}}.complete(req);
        }
    };
}

#endif /* !EXAMPLE_UTILS_HTTP_FRAMEWORK_H */
