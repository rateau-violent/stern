include(FetchContent)

find_package(CURL REQUIRED)

add_library(stern_integration_test_helper
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client.cpp
)

target_include_directories(stern_integration_test_helper
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
    ${CURL_INCLUDE_DIR}
)

target_link_libraries(stern_integration_test_helper
    http
    ${CURL_LIBRARY}
)
