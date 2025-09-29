cmake_minimum_required(VERSION 3.22)

project(Stern)
set(CMAKE_CXX_STANDARD 20)


#### reflect-cpp
add_subdirectory(vendors/reflect-cpp)
target_compile_definitions(reflectcpp PUBLIC REFLECT_CPP_C_ARRAYS_OR_INHERITANCE)
set(REFLECTCPP_AVRO ON) # Optional
set(REFLECTCPP_BSON ON) # Optional
set(REFLECTCPP_CBOR ON) # Optional
set(REFLECTCPP_FLEXBUFFERS ON) # Optional
set(REFLECTCPP_MSGPACK ON) # Optional
set(REFLECTCPP_TOML ON) # Optional
set(REFLECTCPP_UBJSON ON) # Optional
set(REFLECTCPP_XML ON) # Optional
set(REFLECTCPP_YAML ON) # Optional
###

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
