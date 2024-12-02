#ifndef EXAMPLE_USER_CONTROLLER_H
#define EXAMPLE_USER_CONTROLLER_H

#include "utils.h"

namespace example {
    class user_controller : public controller {
        public:
            user_controller();

        private:
            std::vector<std::string> _users;

            http::response _get_users(const http::request& req);
            http::response _post_user(const http::request& req);
            http::response _delete_user(const http::request& req);
            http::response _update_user(const http::request& req);
    };
}

#endif /* !EXAMPLE_USER_CONTROLLER_H */
