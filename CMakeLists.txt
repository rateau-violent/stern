cmake_minimum_required(VERSION 3.22)

project(Backend)
set(CMAKE_CXX_STANDARD 20)
add_subdirectory(lib)

add_subdirectory(example)

list (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

option (ENABLE_TESTS "Build tests along with the library" OFF)
if (ENABLE_TESTS)
    # Check for criterion
    find_package (Criterion REQUIRED)

    # Add tests
    enable_testing ()
    
    add_subdirectory (lib/http/tests)
endif ()
