#include "user/user_module.h"
#include "user/user_controller.h"

namespace example {
    user_module::user_module() {
        _emplace_controller<user_controller>();
    }
}
