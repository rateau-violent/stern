set(CMAKE_CXX_STANDARD 20)

add_library(http STATIC
    include/http/status.h

    src/body.cpp
    src/error.cpp
    src/methods.cpp
    src/query.cpp
    src/request.cpp
    src/response.cpp
    src/versions.cpp
    src/utils/string_helper.cpp
)

target_include_directories(http PUBLIC
    include
)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(http PUBLIC nlohmann_json::nlohmann_json)

set_target_properties(http PROPERTIES LINKER_LANGUAGE CXX)
