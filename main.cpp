#include "lib/backend/include/backend/controller_base.h"

#include "lib/http/include/http/method.h"
#include "lib/http/include/http/request.h"
#include "lib/http/include/http/response.h"

#include <iostream>
#include <functional>
#include <memory>

struct HttpModule {
  using method_type = http::methods;
  using response_type = http::response;
  using request_type = http::request;
};

using route = std::function<http::response (http::request)>;
using controller = backend::controller_base<HttpModule, route>;
using controller_container = std::vector<std::unique_ptr<controller>>;

class users_controller : public controller {
  public:
    users_controller(): controller("/users"), _users{} {
      emplace_routes({
        { "", http::methods::GET, [this] (const http::request &req) { return _get_users(req); } },
        { "", http::methods::POST, [this] (const http::request &req) { return _post_user(req); } },
        { "", http::methods::DELETE, [this] (const http::request &req) { return _delete_user(req); } },
        { "", http::methods::PUT, [this] (const http::request &req) { return _update_user(req); } }
      });
    }

  private:
    std::vector<std::string> _users;

    http::response _get_users(const http::request& req) {
      std::cout << "GET USER" << std::endl;
        for (const auto u: _users) {
          std::cout << "  " << u << std::endl;
        }
        return {};
      }

    http::response _post_user(const http::request& req) {
      std::cout << "POST USER" << std::endl;
      _users.emplace_back("John Doe");
      return {};
    }

    http::response _delete_user(const http::request& req) {
      std::cout << "DELETE USER" << std::endl;
      if (_users.empty()) {
        return {};
      }
      _users.pop_back();
      return {};
    }

    http::response _update_user(const http::request& req) {
      std::cout << "UPDATE USER" << std::endl;
      if (_users.empty()) {
        return {};
      }
      _users.pop_back();
      _users.emplace_back("Mimy Mathy");
      return {};
    }
};

http::request get_request() {
  static const std::vector<http::request> requests{
      {"/users", http::methods::POST },
      {"/users", http::methods::PUT },
      {"/users", http::methods::GET },
      {"/users", http::methods::DELETE }
  };

  std::size_t req = std::rand() % (requests.size() - 1);

  std::cout<< "req index = " << req << std::endl;

  return requests[req];
}

http::response request_handler(controller_container& controllers, const http::request& req) {
  for (auto& ctrl_ptr: controllers) {
    if (auto res = (*ctrl_ptr)(req) ; res != std::nullopt) {
      return (*res);
    }
  }

  throw std::runtime_error("404 not found.");
}

void start_server(controller_container& controllers) {
  for (std::size_t i = 0; i < 15; ++i) {
    try {
      auto req = get_request();

      std::cout << "RECEIVED REQUEST: " << (int)(req.method) << " " << req.path << std::endl;

      auto res = request_handler(controllers, req);

      std::cout << "OK" << std::endl;
      std::cout << "----------" << std::endl;
     } catch (const std::exception& e) {
      std::cerr << "ERROR: " << e.what() << std::endl;
    }
  }
}

int main() {
  std::vector<std::unique_ptr<controller>> controllers {
  };

  controllers.emplace_back(std::make_unique<users_controller>());

  start_server(controllers);

  return 0;
}
