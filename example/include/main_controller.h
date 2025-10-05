#ifndef EXAMPLE_MAIN_CONTROLLER_H
#define EXAMPLE_MAIN_CONTROLLER_H

#include "utils/utils.h"

namespace example {
    class main_controller: public controller {
        public:
            main_controller();

        private:
            http::response _basic_get(const http::request& req);
    };

}

#endif /* !EXAMPLE_MAIN_CONTROLLER_H */