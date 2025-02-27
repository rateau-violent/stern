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

list (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

option (ENABLE_TESTS "Build tests along with the library" OFF)
if (ENABLE_TESTS)
    # Check for criterion
    find_package (Criterion REQUIRED)

    # Add tests
    enable_testing ()
    add_subdirectory (tests)
endif ()