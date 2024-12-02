#ifndef EXAMPLE_UTILS_H
#define EXAMPLE_UTILS_H

#include <functional>
#include <memory>

#include <http/method.h>
#include <http/response.h>
#include <http/request.h>

#include <backend/controller_base.h>
#include <backend/module_base.h>

#include "http/framework.h"

namespace example {
    using route = std::function<http::response (http::request)>;
    using controller = backend::controller_base<http::framework, route>;
    using controller_container = std::vector<std::unique_ptr<controller>>;
    using module = backend::module_base<http::framework, route>;
}

#endif /* !EXAMPLE_UTILS_H */
