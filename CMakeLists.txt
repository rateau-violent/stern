cmake_minimum_required(VERSION 3.22)

project(Backend)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)

add_executable(backend_cpp
        main.cpp
)

target_link_libraries(backend_cpp
    backend
)