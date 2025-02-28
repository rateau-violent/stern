#include <criterion/criterion.h>

#include <http/request.h>

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
    cr_assert_eq(req.body, R"({"name": "John Doe"})");
}
