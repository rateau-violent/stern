#include <criterion/criterion.h>

#include <http/methods.h>

Test(methods, to_method) {
    cr_assert_eq(http::to_method("GET"), http::methods::GET);
    cr_assert_eq(http::to_method("HEAD"), http::methods::HEAD);
    cr_assert_eq(http::to_method("POST"), http::methods::POST);
    cr_assert_eq(http::to_method("PUT"), http::methods::PUT);
    cr_assert_eq(http::to_method("DELETE"), http::methods::DELETE);
    cr_assert_eq(http::to_method("CONNECT"), http::methods::CONNECT);
    cr_assert_eq(http::to_method("OPTIONS"), http::methods::OPTIONS);
    cr_assert_eq(http::to_method("TRACE"), http::methods::TRACE);
    cr_assert_eq(http::to_method("PATCH"), http::methods::PATCH);
    cr_assert_throw(http::to_method("qwerty"), std::runtime_error);
}

Test(methods, to_string) {
    cr_assert_eq(std::to_string(http::methods::GET), "GET");
    cr_assert_eq(std::to_string(http::methods::HEAD), "HEAD");
    cr_assert_eq(std::to_string(http::methods::POST), "POST");
    cr_assert_eq(std::to_string(http::methods::PUT), "PUT");
    cr_assert_eq(std::to_string(http::methods::DELETE), "DELETE");
    cr_assert_eq(std::to_string(http::methods::CONNECT), "CONNECT");
    cr_assert_eq(std::to_string(http::methods::OPTIONS), "OPTIONS");
    cr_assert_eq(std::to_string(http::methods::TRACE), "TRACE");
    cr_assert_eq(std::to_string(http::methods::PATCH), "PATCH");
}
