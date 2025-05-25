#include "user/user_controller.h"


namespace example {
    user_controller::user_controller(): controller("/users"), _users{} {
        emplace_routes({
          { "", http::methods::GET, [this] (const http::request &req) { return _get_users(req); } },
          // { "", http::methods::POST, [this] (const http::request &req) { return _post_user(req); } },
          { "", http::methods::DELETE, [this] (const http::request &req) { return _delete_user(req); } },
          { "", http::methods::PUT, [this] (const http::request &req) { return _update_user(req); } }
        });
        emplace_route<user_dto>("", http::methods::POST, [this] (const http::request& req, const user_dto& user) {
            return _post_user(req, user);
        });
    }

    http::response user_controller::_get_users(const http::request& req) {
        std::cout << "GET USER" << std::endl;
        for (const auto u: _users) {
            std::cout << "  " << u << std::endl;
        }
        return {http::codes::OK, nlohmann::json::array()};
    }

    http::response user_controller::_post_user(const http::request& req, const user_dto& user) {
        std::cout << "POST USER " << user.first_name << " " << user.last_name << std::endl;
        _users.emplace_back(user.first_name + " " + user.last_name);
        return {http::codes::CREATED, "CREATED"};
    }

    http::response user_controller::_delete_user(const http::request& req) {
        std::cout << "DELETE USER" << std::endl;
        if (_users.empty()) {
            throw http::error::bad_request{};
        }
        _users.pop_back();
        return {http::codes::OK, "OK"};
    }

    http::response user_controller::_update_user(const http::request& req) {
        std::cout << "UPDATE USER" << std::endl;
        if (_users.empty()) {
            throw http::error::bad_request{};
        }
        _users.pop_back();
        _users.emplace_back("Mimy Mathy");
        return {http::codes::OK, "OK"};
    }
}