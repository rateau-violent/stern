add_subdirectory(helper)

add_executable(stern_tests
    test_integration.cpp
    fixture/test_fixture.cpp

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
    stern_integration_test_helper
)

add_test(NAME stern_tests COMMAND stern_tests)
