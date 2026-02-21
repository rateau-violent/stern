#include "helper/client.h"
#include "fixture/test_fixture.h"

#include "stern/stern.h"

#include <criterion/criterion.h>

void setup() {
    test_fixture::get_instance().start_server();
}

void tear_down() {
    test_fixture::get_instance().stop_server();
}

Test(stern_integration_tests, base, .init = setup, .fini = tear_down) {

    tests::helper::client client("127.0.0.1", 3000);

    { // post on /users route
        auto res = client.post("users", http::body_type{nlohmann::json{
            {"first_name", "John"},
            {"last_name", "Doe"},
            {"age", 42}
            }});

        cr_assert_eq(res.getCode(), http::codes::CREATED);
    }

    { // get all created users
        auto res = client.get("users");

        cr_assert_eq(res.getCode(), http::codes::OK);
        cr_assert_eq(res.getBody().is_json(), true);
        auto body = nlohmann::json::parse(res.getBody().to_string());
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
        auto res = client.put("users?id=0", http::body_type{nlohmann::json{
            {"first_name", "Isabelle"},
            {"last_name", "Durant"},
            {"age", 84}
        }});
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
}
