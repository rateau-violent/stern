function(add_example_api_test)
    set(options "")
    set(oneValueArgs "NAME")
    set(multipleValueArgs "FILES")

    cmake_parse_arguments(ARG
        "${options}" "${oneValueArgs}" "${multipleValueArgs}"
        ${ARGN}
    )

    add_executable(test_example_api_${ARG_NAME}
        ${ARG_FILES}
        ${CMAKE_SOURCE_DIR}/example/src/main_controller.cpp
        ${CMAKE_SOURCE_DIR}/example/src/main_module.cpp
        ${CMAKE_SOURCE_DIR}/example/src/user/user_controller.cpp
        ${CMAKE_SOURCE_DIR}/example/src/user/user_module.cpp
    )

    include_directories(
        ${CMAKE_SOURCE_DIR}/example/include
    )

    target_link_libraries(test_example_api_${ARG_NAME}
        http
        tests
        stern
        ${CRITERION_LIBRARIES}
    )

    add_test(NAME example.api.${ARG_NAME} COMMAND test_example_api_${ARG_NAME} -j1)
endfunction()

add_example_api_test(NAME users FILES ${CMAKE_CURRENT_SOURCE_DIR}/test_users.cpp)
#add_example_api_test(NAME path FILES ${CMAKE_CURRENT_SOURCE_DIR}/test_path.cpp)
