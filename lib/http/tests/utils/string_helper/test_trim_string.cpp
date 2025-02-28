#include <criterion/criterion.h>

#include <http/utils/string_helper.h>

Test(trim_string, trim_begining_of_str) {
    const std::string str{"     This is a test"};
    constexpr char delimiter{' '};

    auto trim_str = http::utils::trim_string(str, delimiter);

    cr_assert_eq(trim_str, "This is a test");
}

Test(trim_string, trim_end_of_str) {
    const std::string str{"This is a test   "};
    constexpr char delimiter{' '};

    auto trim_str = http::utils::trim_string(str, delimiter);

    cr_assert_eq(trim_str, "This is a test");
}

Test(trim_string, trim_begining_and_end_of_str) {
    const std::string str{" This is a test   "};
    constexpr char delimiter{' '};

    auto trim_str = http::utils::trim_string(str, delimiter);

    cr_assert_eq(trim_str, "This is a test");
}
