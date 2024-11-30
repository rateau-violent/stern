

#include "lib/backend/include/backend/controller_base.h"

#include "lib/http/include/http/method.h"
#include "lib/http/include/http/request.h"
#include "lib/http/include/http/response.h"

#include <iostream>
#include <functional>

struct HttpModule {
  using method_type = http::methods;
  using response_type = http::response;
  using request_type = http::request;
};

template<typename Req, typename Res>
using route = std::function<Res (Req)>;


int main() {

  backend::controller_base<HttpModule, route<http::request, http::response>> c;

  c.emplace_routes({
    { "/", http::methods::GET, [] (const http::request&) {
        std::cout << "test" << std::endl;
        return http::response{};
      }
    }
  });

  http::request req1("/", http::methods::GET);
  
  auto res = c(req1);

  return 0;
}
