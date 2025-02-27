add_executable(http_tests
        test.cpp
)

target_link_libraries(http_tests
    http
    ${CRITERION_LIBRARIES}
)

set_target_properties(http_tests PROPERTIES LINKER_LANGUAGE CXX)

add_test(NAME http_tests COMMAND http_tests)
