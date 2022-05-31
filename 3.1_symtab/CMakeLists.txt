cmake_minimum_required(VERSION 3.15)

project(3.1_symtab VERSION 1.0.1 DESCRIPTION "KPL semantic 1")

add_library(3.1_symtab_lib STATIC debug.c symtab.c debug.h symtab.h)
target_include_directories(3.1_symtab_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(3.1_symtab_lib PROPERTIES 
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

add_executable(3.1_symtab main.c)

target_link_libraries(3.1_symtab 3.1_symtab_lib)
