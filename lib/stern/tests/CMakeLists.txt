find_package(asio REQUIRED)

add_executable(stern_tests
        test_integration.cpp

#        helper/test_fixture.cpp

        ${CMAKE_SOURCE_DIR}/example/src/main_controller.cpp
        ${CMAKE_SOURCE_DIR}/example/src/main_module.cpp
        ${CMAKE_SOURCE_DIR}/example/src/user/user_controller.cpp
        ${CMAKE_SOURCE_DIR}/example/src/user/user_module.cpp
)

include_directories(
    ${CMAKE_SOURCE_DIR}/example/include
)

target_link_libraries(stern_tests
    http
    stern
    ${CRITERION_LIBRARIES}
    asio::asio
)

add_test(NAME stern_tests COMMAND stern_tests)
