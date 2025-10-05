#ifndef EXAMPLE_UTILS_H
#define EXAMPLE_UTILS_H

#include <functional>
#include <memory>

#include <http/methods.h>
#include <http/response.h>
#include <http/request.h>

#include <stern/controller_base.h>
#include <stern/module_base.h>

#include "utils/http_framework.h"

namespace example {
    using controller = stern::controller_base<http_framework>;
    using controller_container = std::vector<std::unique_ptr<controller>>;
    using module = stern::module_base<http_framework>;
}

#endif /* !EXAMPLE_UTILS_H */
