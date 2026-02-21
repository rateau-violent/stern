add_subdirectory(helper)

function(add_stern_test)
    set(options "")
    set(oneValueArgs "NAME")
    set(multipleValueArgs "FILES")

    cmake_parse_arguments(ARG
        "${options}" "${oneValueArgs}" "${multipleValueArgs}"
        ${ARGN}
    )

    add_executable(${ARG_NAME}
        ${ARG_FILES}
        fixture/test_fixture.cpp
        ${CMAKE_SOURCE_DIR}/example/src/main_controller.cpp
        ${CMAKE_SOURCE_DIR}/example/src/main_module.cpp
        ${CMAKE_SOURCE_DIR}/example/src/user/user_controller.cpp
        ${CMAKE_SOURCE_DIR}/example/src/user/user_module.cpp
    )

    include_directories(
        ${CMAKE_SOURCE_DIR}/example/include
    )

    target_link_libraries(${ARG_NAME}
        http
        stern
        ${CRITERION_LIBRARIES}
        stern_integration_test_helper
    )

    add_test(NAME stern.${ARG_NAME} COMMAND ${ARG_NAME} -j1)
endfunction()

add_stern_test(NAME integration FILES ${CMAKE_CURRENT_SOURCE_DIR}/test_integration.cpp)
add_stern_test(NAME path FILES ${CMAKE_CURRENT_SOURCE_DIR}/test_path.cpp)
