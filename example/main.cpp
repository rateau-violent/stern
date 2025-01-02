#include <functional>

#include "utils.h"

#include "main_module.h"

#include <backend/server.h>


int main() {
  backend::server<http::framework, example::route> server(3000, example::main_module());

  server.start();

  return 0;
}
