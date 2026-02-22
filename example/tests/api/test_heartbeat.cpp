#include "tests/http_client.h"
#include "tests/fixture.h"

#include "stern/stern.h"

#include <criterion/criterion.h>
#include <main_module.h>
#include <utils/http_framework.h>


using http_framework = example::http_framework;
using fixture_type = tests::fixture<http_framework>;

static void setup() {
  fixture_type::get_instance(example::main_module()).start_server();
}

static void tear_down() {
  fixture_type::get_instance(example::main_module()).stop_server();
  // make sure tests do not overlap
  sleep(1);
}

Test(example_heartbeat_tests, get, .init = setup, .fini = tear_down) {
  tests::http_client client("127.0.0.1", 3000);

  auto res = client.get("/");
  cr_assert_eq(res.getCode(), http::codes::OK);
}

Test(example_heartbeat_tests, post, .init = setup, .fini = tear_down) {
  tests::http_client client("127.0.0.1", 3000);

  auto res = client.post("/", http::body_type{nlohmann::json::object()});
  cr_assert_eq(res.getCode(), http::codes::NOT_FOUND);
}

Test(example_heartbeat_tests, put, .init = setup, .fini = tear_down) {
  tests::http_client client("127.0.0.1", 3000);

  auto res = client.put("/", http::body_type{nlohmann::json::object()});
  cr_assert_eq(res.getCode(), http::codes::NOT_FOUND);
}

Test(example_heartbeat_tests, delete, .init = setup, .fini = tear_down) {
  tests::http_client client("127.0.0.1", 3000);

  auto res = client.del("/");
  cr_assert_eq(res.getCode(), http::codes::NOT_FOUND);
}
