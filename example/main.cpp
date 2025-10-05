#include <functional>

#include "utils/utils.h"

#include "main_module.h"

#include <stern/server.h>


int main() {
  stern::server<example::http_framework> server(3000, example::main_module());

  server.start();

  return 0;
}
