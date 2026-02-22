include(FetchContent)

find_package(CURL REQUIRED)

add_library(tests
    ${CMAKE_CURRENT_SOURCE_DIR}/src/http_client.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tests/fixture.h
)

target_include_directories(tests
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
    ${CURL_INCLUDE_DIR}
)

target_link_libraries(tests
    stern
    http
    ${CURL_LIBRARY}
)
