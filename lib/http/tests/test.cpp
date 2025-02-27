#include <criterion/criterion.h>

#include <string>

Test(strlen, empty) {
    cr_assert_eq(std::strlen(""), 0);
}
