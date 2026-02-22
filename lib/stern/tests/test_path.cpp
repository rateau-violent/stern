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
  // sleep to avoid address conflicts
  sleep(1);
}

Test(stern_test_path, regular_amount_slashes, .init = setup, .fini = tear_down) {
  tests::http_client client("127.0.0.1", 3000);

  auto res = client.get("users");

  cr_assert_eq(res.getCode(), http::codes::OK);
}


Test(stern_test_path, multiple_slashes_before, .init = setup, .fini = tear_down) {
  tests::http_client client("127.0.0.1", 3000);

  auto res = client.get("///users");

  cr_assert_eq(res.getCode(), http::codes::OK);
}

Test(stern_test_path, multiple_slashes_after, .init = setup, .fini = tear_down) {
  tests::http_client client("127.0.0.1", 3000);

  auto res = client.get("users////");

  cr_assert_eq(res.getCode(), http::codes::OK);
}
