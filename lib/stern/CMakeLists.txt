add_library(stern STATIC
    include/stern/stern.h
    include/stern/controller_base.h
    include/stern/framework.h
    include/stern/module_base.h
    include/stern/parameters.h
    include/stern/server.h
)

target_link_libraries(stern
    http
    network
    reflectcpp
)

target_include_directories(stern PUBLIC
    include
)

set_target_properties(stern PROPERTIES LINKER_LANGUAGE CXX)
