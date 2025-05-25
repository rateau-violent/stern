#ifndef EXAMPLE_UTILS_H
#define EXAMPLE_UTILS_H

#include <functional>
#include <memory>

#include <http/methods.h>
#include <http/response.h>
#include <http/request.h>

#include <backend/controller_base.h>
#include <backend/module_base.h>

#include "http/framework.h"

namespace example {
    using controller = backend::controller_base<http::framework>;
    using controller_container = std::vector<std::unique_ptr<controller>>;
    using module = backend::module_base<http::framework>;
}

#endif /* !EXAMPLE_UTILS_H */
