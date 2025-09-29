#ifndef EXAMPLE_UTILS_H
#define EXAMPLE_UTILS_H

#include <functional>
#include <memory>

#include <http/methods.h>
#include <http/response.h>
#include <http/request.h>

#include <stern/controller_base.h>
#include <stern/module_base.h>

#include "http/framework.h"

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
    };

    using controller = stern::controller_base<http_framework>;
    using controller_container = std::vector<std::unique_ptr<controller>>;
    using module = stern::module_base<http_framework>;
}

#endif /* !EXAMPLE_UTILS_H */
