#include <criterion/criterion.h>

#include <http/utils/string_helper.h>

Test(split_string_at_first_delimiter, split_one_char_delimiter) {
    const std::string str{"value:abc"};
    const std::string delimiter{":"};

    auto [first, second] = http::utils::split_string_at_first_delimiter(str, delimiter);

    cr_assert_eq(first, "value");
    cr_assert_eq(second, "abc");
}

Test(split_string_at_first_delimiter, multiple_delimiters_in_string) {
    const std::string str{"value:abc:test"};
    const std::string delimiter{":"};

    auto [first, second] = http::utils::split_string_at_first_delimiter(str, delimiter);

    cr_assert_eq(first, "value");
    cr_assert_eq(second, "abc:test");
}

Test(split_string_at_first_delimiter, delimiter_is_multiple_char) {
    const std::string str{"This  is a  test"};
    const std::string delimiter{"  "};

    auto [first, second] = http::utils::split_string_at_first_delimiter(str, delimiter);

    cr_assert_eq(first, "This");
    cr_assert_eq(second, "is a  test");
}

Test(split_string_at_first_delimiter, str_is_empty) {
    const std::string str{};
    const std::string delimiter{":"};

    auto [first, second] = http::utils::split_string_at_first_delimiter(str, delimiter);

    cr_assert(first.empty());
    cr_assert(second.empty());
}

Test(split_string_at_first_delimiter, delimiter_is_empty) {
    const std::string str{"test:abc"};
    const std::string delimiter{};

    auto [first, second] = http::utils::split_string_at_first_delimiter(str, delimiter);

    cr_assert_eq(first, "test:abc");
    cr_assert(second.empty());
}

Test(split_string_at_first_delimiter, no_delimiter_in_str) {
    const std::string str{"test:abc"};
    const std::string delimiter(" ");

    auto [first, second] = http::utils::split_string_at_first_delimiter(str, delimiter);

    cr_assert_eq(first, "test:abc");
    cr_assert(second.empty());
}

Test(split_string_at_first_delimiter, delimiter_is_at_begining_of_string) {
    const std::string str{":abc"};
    const std::string delimiter{":"};

    auto [first, second] = http::utils::split_string_at_first_delimiter(str, delimiter);

    cr_assert(first.empty());
    cr_assert_eq(second, "abc");
}

Test(split_string_at_first_delimiter, delimiter_is_at_end_of_string) {
    const std::string str{"test:"};
    const std::string delimiter{":"};

    auto [first, second] = http::utils::split_string_at_first_delimiter(str, delimiter);

    cr_assert_eq(first, "test");
    cr_assert(second.empty());
}
