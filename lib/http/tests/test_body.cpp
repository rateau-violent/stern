#include <criterion/criterion.h>

#include <http/body.h>

Test(body, string_constructor) {
    { // construct from basic string
        const std::string str = R"(Hello, World!)";
        http::body_type b(str);

        cr_assert(b.is_json() == false);
        cr_assert_eq(b.to_string(), str);
    }
    { // construct from empty string
        const std::string str;
        http::body_type b(str);

        cr_assert(b.is_json() == false);
        cr_assert_eq(b.to_string(), str);
    }
    { // construct from json string
        const std::string str = R"({ "name": "John Doe", "age": 42 })";
        http::body_type b(str);

        cr_assert(b.is_json());
    }
}

Test(body, json_contructor) {
    auto obj = nlohmann::json::parse(R"({ "name": "John Doe", "age": 42 })");

    http::body_type b(obj);
    cr_assert(b.is_json());
}
