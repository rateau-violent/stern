#include <criterion/criterion.h>

#include <http/query.h>

Test(query, default_constructor) {
    http::query_type q;

    cr_assert(q.empty() == true);
}

Test(query, string_constructor) {
    { // construct from empty string
        const std::string str = "";
        http::query_type q(str);

        cr_assert(q.empty() == true);
    }
    { // one number parameter
        const std::string str = "id=1";
        http::query_type q(str);

        cr_assert(q.empty() == false);
        cr_assert_eq(q.to_string(), R"({"id":1})");
    }
    { // multiple number parameters
        const std::string str = "ids=1,2,4,5";
        http::query_type q(str);

        cr_assert(q.empty() == false);
        cr_assert_eq(q.to_string(), R"({"ids":[1,2,4,5]})");
    }
    { // one string parameter
        const std::string str = "name=Doe";
        http::query_type q(str);

        cr_assert(q.empty() == false);
        cr_assert_eq(q.to_string(), R"({"name":"Doe"})");
    }
    { // multiple string parameter
        const std::string str = "names=John,Doe";
        http::query_type q(str);

        cr_assert(q.empty() == false);
        cr_assert_eq(q.to_string(), R"({"names":["John","Doe"]})");
    }
    { // multiple parameters
        const std::string str = "name=Doe&age=42";

        http::query_type q(str);

        cr_assert(q.empty() == false);
        cr_assert_eq(q.to_string(), R"({"age":42,"name":"Doe"})");
    }
}
