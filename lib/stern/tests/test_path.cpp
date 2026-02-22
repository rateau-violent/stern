#include "helper/client.h"
#include "fixture/test_fixture.h"

#include "stern/stern.h"

#include <criterion/criterion.h>

static void setup() {
  test_fixture::get_instance().start_server();
}

static void tear_down() {
  test_fixture::get_instance().stop_server();
  // mandatory sleep when multiple tests
  sleep(1);
}


Test(stern_test_path, regular_amount_slashes, .init = setup, .fini = tear_down) {
  tests::helper::client client("127.0.0.1", 3000);

  auto res = client.get("users");

  cr_assert_eq(res.getCode(), http::codes::OK);
}


Test(stern_test_path, multiple_slashes_before, .init = setup, .fini = tear_down) {
  tests::helper::client client("127.0.0.1", 3000);

  auto res = client.get("///users");

  cr_assert_eq(res.getCode(), http::codes::OK);
}

Test(stern_test_path, multiple_slashes_after, .init = setup, .fini = tear_down) {
  tests::helper::client client("127.0.0.1", 3000);

  auto res = client.get("users////");

  cr_assert_eq(res.getCode(), http::codes::OK);
}
