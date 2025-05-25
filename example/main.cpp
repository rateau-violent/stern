#include <functional>

#include "utils.h"

#include "main_module.h"

#include <backend/server.h>


int main() {
  backend::server<example::http_framework> server(3000, example::main_module());

  server.start();

  return 0;
}
