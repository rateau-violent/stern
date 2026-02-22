#ifndef STERN_TEST_FIXTURE_H
#define STERN_TEST_FIXTURE_H


#include <thread>

#include <stern/framework.h>
#include <stern/server.h>
#include <stern/module_base.h>

namespace tests {

template <stern::Framework F>
class fixture {
public:
  using server_type = stern::server<F>;
  using module_type = stern::module_base<F>;

  static fixture &get_instance(module_type&& main_module, std::size_t port = 3000) {
    static fixture helper{std::move(main_module), port};

    return helper;
  }

  void start_server() {
    _server_thread = std::jthread([this]() {
      _server_instance.start();
    });
    // mandatory sleep to let the server start properly
    sleep(1);
  }

  void stop_server() {
    sleep(1);
    _server_instance.stop();
    sleep(1);
    _server_thread.request_stop();
  }

private:
  std::jthread _server_thread;
  server_type _server_instance;

  std::size_t _port{0};

  explicit fixture(module_type&& main_module, std::size_t port):
    _server_instance(port, std::move(main_module))  {
  };
};

} // namespace tests

#endif
