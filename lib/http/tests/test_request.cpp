#include <criterion/criterion.h>

#include <http/request.h>

#include <iostream>

Test(request, get_request_create_from_string) {
    const std::string request_str{
        "GET / HTTP/1.1\r\n"
        "Host: localhost:3000\r\n"
        "\r\n"
    };

    const http::request req(request_str);

    cr_expect_eq(req.version, http::versions::HTTP_1_1);
    cr_expect_eq(req.path, "/");
    cr_expect_eq(req.method, http::methods::GET);
    cr_expect_eq(req.headers.size(), 1);
    cr_assert_eq(req.headers.at("Host"), "localhost:3000");
    cr_assert(req.query.empty());
}

Test(request, post_request_with_body_create_from_string) {
    const std::string request_str{
        "POST /users HTTP/0.9\r\n"
        "Host: localhost:3000\r\n"
        "User-Agent: curl/7.81.0\r\n"
        "Accept: */*\r\n"
        "\r\n"
        R"({"name": "John Doe"})"
    };

    const http::request req(request_str);

    cr_assert_eq(req.version, http::versions::HTTP_0_9);
    cr_assert_eq(req.path, "/users");
    cr_assert_eq(req.method, http::methods::POST);
    cr_assert_eq(req.headers.size(), 3);
    cr_assert_eq(req.headers.at("Host"), "localhost:3000");
    cr_assert_eq(req.headers.at("User-Agent"), "curl/7.81.0");
    cr_assert_eq(req.headers.at("Accept"), "*/*");
    cr_assert(req.body.is_json());
    cr_assert_eq(req.body.to_string(), nlohmann::to_string(nlohmann::json::parse(R"({"name": "John Doe"})")));
    cr_assert(req.query.empty());
}

Test(request, one_query_parameter) {
    const std::string request_str{
        "GET /users?id=abcd HTTP/1.1\r\n"
        "Host: localhost:3000\r\n"
        "\r\n"
    };

    const http::request req(request_str);

    cr_assert_eq(req.query.to_string(), nlohmann::to_string(nlohmann::json::parse(R"({"id":"abcd"})")));
}

Test(request, multiple_query_parameter) {
    const std::string request_str{
        "GET /users?age=42&single=true HTTP/1.1\r\n"
        "Host: localhost:3000\r\n"
        "\r\n"
    };

    const http::request req(request_str);

    cr_assert_eq(req.query.to_string(), nlohmann::to_string(nlohmann::json::parse(R"({"age":42,"single":true})")));
}

Test(request, query_parameter_without_value) {
    const std::string request_str{
        "GET /users?single HTTP/1.1\r\n"
        "Host: localhost:3000\r\n"
        "\r\n"
    };

    const http::request req(request_str);

    cr_assert_eq(req.query.to_string(), nlohmann::to_string(nlohmann::json::parse(R"({"single":""})")));
}

Test(request, query_parameter_with_comma) {
    const std::string request_str{
        "GET /users?hair=short,long HTTP/1.1\r\n"
        "Host: localhost:3000\r\n"
        "\r\n"
    };

    const http::request req(request_str);

    cr_assert_eq(req.query.to_string(), nlohmann::to_string(nlohmann::json::parse(R"({"hair":["short","long"]})")));
}

Test(request, query_parameter_with_negative_number) {
    const std::string request_str{
        "GET /users?tooth=-1 HTTP/1.1\r\n"
        "Host: localhost:3000\r\n"
        "\r\n"
    };

    const http::request req(request_str);

    cr_assert_eq(req.query.to_string(), nlohmann::to_string(nlohmann::json::parse(R"({"tooth":-1})")));
}
