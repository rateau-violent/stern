#ifndef EXAMPLE_USER_DTO_H
#define EXAMPLE_USER_DTO_H

#include <string>

namespace example {

    struct user_dto: backend::parameter::body {
      std::string first_name;
      std::string last_name;
      int age;
    };
}

#endif /* !EXAMPLE_USER_DTO_H */