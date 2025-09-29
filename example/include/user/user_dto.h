#ifndef EXAMPLE_USER_DTO_H
#define EXAMPLE_USER_DTO_H

#include <string>

namespace example {

    struct user_dto: stern::parameter::body {
      std::string first_name;
      std::string last_name;
      std::size_t age;
    };

    struct user_id: stern::parameter::uri {
        std::size_t id;
    };
}

#endif /* !EXAMPLE_USER_DTO_H */