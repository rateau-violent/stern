set(CMAKE_CXX_STANDARD 20)

add_library(http STATIC
    include/http/framework.h
    include/http/response.h
    include/http/status.h

    src/methods.cpp
    src/request.cpp
    src/versions.cpp
    src/utils/string_helper.cpp
)

target_include_directories(http PUBLIC
    include
)

set_target_properties(http PROPERTIES LINKER_LANGUAGE CXX)
