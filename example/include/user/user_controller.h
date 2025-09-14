#ifndef EXAMPLE_USER_CONTROLLER_H
#define EXAMPLE_USER_CONTROLLER_H

#include "utils.h"
#include "user/user_dto.h"

namespace example {
    class user_controller : public controller {
        public:
            user_controller();

        private:
            struct user {
                std::string first_name;
                std::string last_name;
                std::size_t age;
            };

            std::vector<user> _users;

            http::response _get_users(const http::request& req, const user_id&) const;
            http::response _post_user(const http::request& req, const user_dto& user);
            http::response _delete_user(const http::request& req, const user_id&);
            http::response _update_user(const http::request& req, const user_id&, const user_dto&);
    };
}

#endif /* !EXAMPLE_USER_CONTROLLER_H */
