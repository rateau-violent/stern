add_executable(http_tests
        test_methods.cpp
        test_request.cpp
        test_versions.cpp
)
target_link_libraries(http_tests
    http
    ${CRITERION_LIBRARIES}
)
set_target_properties(http_tests PROPERTIES LINKER_LANGUAGE CXX)
add_test(NAME http_tests COMMAND http_tests)


add_executable(http_utils_tests
    utils/string_helper/test_split_string.cpp
    utils/string_helper/test_split_string_at_first_delimiter.cpp
    utils/string_helper/test_trim_string.cpp
)
target_link_libraries(http_utils_tests http ${CRITERION_LIBRARIES})
add_test(NAME http_utils_tests COMMAND http_utils_tests)
