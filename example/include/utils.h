#ifndef EXAMPLE_UTILS_H
#define EXAMPLE_UTILS_H

#include <functional>
#include <memory>

#include <http/method.h>
#include <http/response.h>
#include <http/request.h>

#include <backend/controller_base.h>
#include <backend/module_base.h>

namespace example {
    struct HttpFramework {
        using method_type = http::methods;
        using response_type = http::response;
        using request_type = http::request;
    };

    using route = std::function<http::response (http::request)>;
    using controller = backend::controller_base<HttpFramework, route>;
    using controller_container = std::vector<std::unique_ptr<controller>>;
    using module = backend::module_base<HttpFramework, route>;
}

#endif /* !EXAMPLE_UTILS_H */
