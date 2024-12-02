#ifndef EXAMPLE_MAIN_MODULE_H
#define EXAMPLE_MAIN_MODULE_H

#include "utils.h"

namespace example {
    class main_module: public backend::module_base<HttpFramework, route> {
        public:
            main_module();
    };
}

#endif /* !EXAMPLE_MAIN_MODULE_H */
