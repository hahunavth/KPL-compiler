cmake_minimum_required(VERSION 3.15)

project(
    3.2_symtab
    VERSION 1.0.1
    DESCRIPTION
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(3.2_symtab_lib STATIC debug.c symtab.c debug.h symtab.h)
target_include_directories(3.1_symtab_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(3.2_symtab_lib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

add_executable(3.2_symtab main.c)

target_link_libraries(3.2_symtab 3.2_symtab_lib)
