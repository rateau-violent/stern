#include "user/user_module.h"

namespace example {
    user_module::user_module() {
        _emplace_controller<user_controller>();
    }
}
