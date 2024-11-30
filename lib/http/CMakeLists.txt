set(CMAKE_CXX_STANDARD 20)

add_library(http STATIC
    include/http/method.h
    include/http/request.h
    include/http/response.h
    include/http/status.h
)

target_include_directories(http PUBLIC
    include
)

set_target_properties(http PROPERTIES LINKER_LANGUAGE CXX)
