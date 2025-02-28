#include <criterion/criterion.h>

#include <http/versions.h>

Test(versions, to_version) {
    cr_assert_eq(http::to_version("HTTP/0.9"), http::versions::HTTP_0_9);
    cr_assert_eq(http::to_version("HTTP/1.0"), http::versions::HTTP_1_0);
    cr_assert_eq(http::to_version("HTTP/1.1"), http::versions::HTTP_1_1);
    cr_assert_eq(http::to_version("HTTP/2"), http::versions::HTTP_2);
    cr_assert_eq(http::to_version("HTTP/3"), http::versions::HTTP_3);
    cr_assert_throw(http::to_version("qwerty"), std::runtime_error);
}

Test(version, to_string) {
    cr_assert_eq(std::to_string(http::versions::HTTP_0_9), "HTTP/0.9");
    cr_assert_eq(std::to_string(http::versions::HTTP_1_0), "HTTP/1.0");
    cr_assert_eq(std::to_string(http::versions::HTTP_1_1), "HTTP/1.1");
    cr_assert_eq(std::to_string(http::versions::HTTP_2), "HTTP/2");
    cr_assert_eq(std::to_string(http::versions::HTTP_3), "HTTP/3");
}