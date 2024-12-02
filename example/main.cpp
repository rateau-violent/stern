#include <iostream>
#include <functional>
#include <memory>

#include "utils.h"

#include "main_module.h"

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

void start_server(backend::module_base<http::framework, example::route>& m_module) {
  srand(time(nullptr));

  for (std::size_t i = 0; i < 15; ++i) {
    try {
      auto req = get_request();

      std::cout << "RECEIVED REQUEST: " << std::to_string(req.method) << " " << req.path << std::endl;

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
  example::main_module m;

  start_server(m);

  return 0;
}
