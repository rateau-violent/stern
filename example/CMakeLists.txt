add_executable(example
        main.cpp
        src/user/user_controller.cpp
        src/user/user_module.cpp
        src/utils/utils.cpp
        src/main_controller.cpp
        src/main_module.cpp
)

include_directories(
        include
)

target_link_libraries(example
        stern
        http
)
