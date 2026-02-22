#include <criterion/criterion.h>

#include <tests/http_client.h>
#include <tests/fixture.h>

#include <stern/stern.h>

#include "main_module.h"
#include "utils/http_framework.h"


using http_framework = example::http_framework;
using fixture_type = tests::fixture<http_framework>;

static void setup() {
  fixture_type::get_instance(example::main_module()).start_server();
}

static void tear_down() {
  fixture_type::get_instance(example::main_module()).stop_server();
}

Test(stern_integration_tests, base, .init = setup, .fini = tear_down) {
  tests::http_client client("127.0.0.1", 3000);

  { // create a new user
    auto res = client.post("users", http::body_type{
                             nlohmann::json{
                               {"first_name", "John"},
                               {"last_name", "Doe"},
                               {"age", 42}
                             }
                           });

    cr_assert_eq(res.getCode(), http::codes::CREATED);
  }

  { // get all users
    auto res = client.get("users");
    cr_assert_eq(res.getCode(), http::codes::OK);
    cr_assert_eq(res.getBody().is_json(), true);
    auto body = nlohmann::json::parse(res.getBody().to_string());
    cr_assert_eq(body.is_array(), true);
    cr_assert_eq(body.size(), 1);
    cr_assert_eq(body[0].at("first_name"), "John");
    cr_assert_eq(body[0].at("last_name"), "Doe");
    cr_assert_eq(body[0].at("age"), 42);
  }

  { // get one particular user
    auto res = client.get("users?id=0");
    cr_assert_eq(res.getCode(), http::codes::OK);
    cr_assert_eq(res.getBody().is_json(), true);
    auto body = nlohmann::json::parse(res.getBody().to_string());
    cr_assert_eq(body.at("first_name"), "John");
    cr_assert_eq(body.at("last_name"), "Doe");
    cr_assert_eq(body.at("age"), 42);
  }

  { // Update user
    auto res = client.put("users?id=0", http::body_type{
                            nlohmann::json{
                              {"first_name", "Isabelle"},
                              {"last_name", "Durant"},
                              {"age", 84}
                            }
                          });
    cr_assert_eq(res.getCode(), http::codes::OK);
  }

  { // get updated user
    auto res = client.get("users?id=0");
    cr_assert_eq(res.getCode(), http::codes::OK);
    cr_assert_eq(res.getBody().is_json(), true);
    auto body = nlohmann::json::parse(res.getBody().to_string());
    cr_assert_eq(body.at("first_name"), "Isabelle");
    cr_assert_eq(body.at("last_name"), "Durant");
    cr_assert_eq(body.at("age"), 84);
  }

  { // delete user
    auto res = client.del("users?id=0");
    cr_assert_eq(res.getCode(), http::codes::OK);
  }

  { // get all users
    auto res = client.get("users");
    cr_assert_eq(res.getCode(), http::codes::OK);
    cr_assert_eq(res.getBody().is_json(), true);
    auto body = nlohmann::json::parse(res.getBody().to_string());
    cr_assert_eq(body.size(), 0);
  }
}
