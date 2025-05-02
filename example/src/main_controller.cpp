#include "main_controller.h"

namespace example {

    main_controller::main_controller(): controller_base("/") {
        emplace_routes({
          { "", http::methods::GET, [this](const http::request& req) { return _basic_get(req); }}
        });
    }

    http::response main_controller::_basic_get(const http::request& req) {
        std::cout << "Everything is all right!" << std::endl;
        return {http::codes::OK, "OK"};
    }
}