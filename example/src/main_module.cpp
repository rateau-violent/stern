#include "main_module.h"
#include "main_controller.h"

#include "user/user_module.h"

namespace example {
    main_module::main_module() {
        _emplace_submodule<user_module>();
        _emplace_controller<main_controller>();
    }
}
