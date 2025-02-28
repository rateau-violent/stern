#include <criterion/criterion.h>

#include <http/utils/string_helper.h>

Test(split_string, split_with_one_char_delimiter) {
    const std::string str{"This is a test"};
    const std::string delimiter{" "};

    auto split_str = http::utils::split_string(str, delimiter);

    cr_assert_eq(split_str.size(), 4);
    cr_assert_eq(split_str[0], "This");
    cr_assert_eq(split_str[1], "is");
    cr_assert_eq(split_str[2], "a");
    cr_assert_eq(split_str[3], "test");
}

Test(split_string, split_with_multiple_chars_delimiter) {
    const std::string str{"This  is a  test"};
    const std::string delimiter{"  "};

    auto split_str = http::utils::split_string(str, delimiter);

    cr_assert_eq(split_str.size(), 3);
    cr_assert_eq(split_str[0], "This");
    cr_assert_eq(split_str[1], "is a");
    cr_assert_eq(split_str[2], "test");
}

Test(split_string, split_empty_string) {
    const std::string str{};
    const std::string delimiter{" "};

    auto split_string = http::utils::split_string(str, delimiter);

    cr_assert_eq(split_string.size(), 0);
}

Test(split_string, empty_delimiter) {
    const std::string str{"This is a test"};
    const std::string delimiter{};

    auto split_string = http::utils::split_string(str, delimiter);

    cr_assert_eq(split_string.size(), 1);
    cr_assert_eq(split_string[0], "This is a test");
}

Test(split_string, delimiter_not_found) {
    const std::string str{"This is a test"};
    const std::string delimiter{";"};

    auto split_string = http::utils::split_string(str, delimiter);

    cr_assert_eq(split_string.size(), 1);
    cr_assert_eq(split_string[0], "This is a test");
}

Test(split_string, str_equal_to_delimiter) {
    const std::string str{";"};
    const std::string delimiter{";"};

    auto split_string = http::utils::split_string(str, delimiter);

    cr_assert_eq(split_string.size(), 2);
    for (std::size_t i = 0; i < split_string.size(); ++i) {
        cr_assert(split_string[i].empty());
    }
}

Test(split_string, str_is_multiple_delimiters) {
    const std::string str{";;;;;;;;;;"};
    const std::string delimiter{";"};

    auto split_string = http::utils::split_string(str, delimiter);

    cr_assert_eq(split_string.size(), 11);
    for (std::size_t i = 0; i < split_string.size(); ++i) {
        cr_assert(split_string[i].empty());
    }
}

Test(split_string, delimiter_is_at_begining_of_str) {
    const std::string str{" This is a test"};
    const std::string delimiter{" "};

    auto split_string = http::utils::split_string(str, delimiter);

    cr_assert_eq(split_string.size(), 5);
    cr_assert_eq(split_string[0], "");
    cr_assert_eq(split_string[1], "This");
    cr_assert_eq(split_string[2], "is");
    cr_assert_eq(split_string[3], "a");
    cr_assert_eq(split_string[4], "test");
}

Test(split_string, delimiter_is_at_end_of_str) {
    const std::string str{"This is a test "};
    const std::string delimiter{" "};

    auto split_string = http::utils::split_string(str, delimiter);

    cr_assert_eq(split_string.size(), 5);
    cr_assert_eq(split_string[0], "This");
    cr_assert_eq(split_string[1], "is");
    cr_assert_eq(split_string[2], "a");
    cr_assert_eq(split_string[3], "test");
    cr_assert_eq(split_string[4], "");
}
