add_compile_options("-D REFLECT_CPP_C_ARRAYS_OR_INHERITANCE")

add_library(backend STATIC
    include/backend/backend.h
    include/backend/controller_base.h
    include/backend/concepts.h
    include/backend/module_base.h
    include/backend/parameters.h
    include/backend/server.h
)

find_package(reflectcpp)

target_link_libraries(backend
    http
    network
    reflectcpp::reflectcpp
)

target_include_directories(backend PUBLIC
    include
    ../http/include # TODO
)

set_target_properties(backend PROPERTIES LINKER_LANGUAGE CXX)