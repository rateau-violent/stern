#include "lib/backend/include/backend/controller_base.h"
#include "lib/backend/include/backend/module_base.h"

#include "lib/http/include/http/method.h"
#include "lib/http/include/http/request.h"
#include "lib/http/include/http/response.h"

#include <iostream>
#include <functional>
#include <memory>

struct HttpFramework {
  using method_type = http::methods;
  using response_type = http::response;
  using request_type = http::request;
};

using route = std::function<http::response (http::request)>;
using controller = backend::controller_base<HttpFramework, route>;
using controller_container = std::vector<std::unique_ptr<controller>>;
using module = backend::module_base<HttpFramework, route>;

template<typename T>
using initializer = std::function<T ()>;

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

class user_module: public module {
  public:
    user_module(): module_base() {
      _emplace_controller<users_controller>();
    }
};

class main_controller: public controller {
  public:
    main_controller(): controller_base("/") {
      emplace_routes({
        { "", http::methods::GET, [this](const http::request& req) { return _basic_get(req); }}
      });
    }

  private:
    http::response _basic_get(const http::request& req) {
      std::cout << "Everything is all right!" << std::endl;
      return {};
    }
};

class main_module: public backend::module_base<HttpFramework, route> {
  public:
    main_module(): module_base() {
      _emplace_submodule<user_module>();
      _emplace_controller<main_controller>();
    }
};

http::request get_request() {
  static const std::vector<http::request> requests{
      {"/users", http::methods::POST },
      {"/users", http::methods::PUT },
      {"/users", http::methods::GET },
      {"/users", http::methods::DELETE },
      {"/", http::methods::GET },
      {"/", http::methods::POST }
  };
  std::size_t req = std::rand() % requests.size();

  return requests[req];
}

void start_server(backend::module_base<HttpFramework, route>& m_module) {
  srand(time(nullptr));

  for (std::size_t i = 0; i < 15; ++i) {
    try {
      auto req = get_request();

      std::cout << "RECEIVED REQUEST: " << (int)(req.method) << " " << req.path << std::endl;

      auto res = m_module(req);

      if (res == std::nullopt) {
        std::cout << "404 Not found" << std::endl;
      } else {
        std::cout << "OK" << std::endl;
      }
      std::cout << "----------" << std::endl;
     } catch (const std::exception& e) {
      std::cerr << "ERROR: " << e.what() << std::endl;
    }
  }
}

int main() {
  main_module m;

  start_server(m);

  return 0;
}
