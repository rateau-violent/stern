#include "user/user_controller.h"


namespace example {
    user_controller::user_controller(): controller("/users"), _users{} {
        emplace_route<user_id>("", http::methods::GET, [this](const auto&req, const auto& query) {
            return _get_users(req, query);
        });
        emplace_route<user_dto>("", http::methods::POST, [this] (const auto& req, const auto& body) {
            return _post_user(req, body);
        });
        emplace_route<user_id>("", http::methods::DELETE, [this](const auto& req, const auto& query) {
            return _delete_user(req, query);
        });
        emplace_route<user_id, user_dto>("", http::methods::PUT, [this](const auto& req, const auto& query, const auto& body) {
            return _update_user(req, query, body);
        });
    }

    http::response user_controller::_get_users(const http::request& req, const user_id& query) const {
        std::cout << "GET USER " << query.id << std::endl;
        if (query.id >= _users.size()) {
            throw http::error::not_found();
        }
        return http::response{http::codes::OK, http::body_type{rfl::json::write(_users[query.id])}};
    }

    http::response user_controller::_post_user(const http::request& req, const user_dto& user) {
        std::cout << "POST USER " << user.first_name << " " << user.last_name << std::endl;
        _users.emplace_back(user.first_name, user.last_name, user.age);
        return http::response{http::codes::CREATED, http::body_type{"CREATED"}};
    }

    http::response user_controller::_delete_user(const http::request& req, const user_id& query) {
        std::cout << "DELETE USER" << std::endl;
        if (_users.size() <= query.id) {
            throw http::error::not_found{};
        }
        _users.erase(_users.begin() + query.id);
        return http::response{http::codes::OK, http::body_type{"OK"}};
    }

    http::response user_controller::_update_user(const http::request& req, const user_id& query, const user_dto& body) {
        std::cout << "UPDATE USER" << std::endl;
        if (query.id >= _users.size()) {
            throw http::error::not_found{};
        }
        auto &u = _users.at(query.id);
        u.first_name = body.first_name;
        u.last_name = body.last_name;
        u.age = body.age;
        return http::response{http::codes::OK, http::body_type{"OK"}};
    }
}
