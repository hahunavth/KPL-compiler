cmake_minimum_required(VERSION 3.15)

project(
    3.4_typechecker
    VERSION 1.0.1
    DESCRIPTION
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(3.4_typechecker_lib STATIC
    charcode.c
    debug.c
    error.c
    main.c
    parser.c
    reader.c
    debug.h
    symtab.h
    scanner.c
    semantics.c
    symtab.c
    token.c
)
target_include_directories(3.4_typechecker_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(3.4_typechecker_lib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

add_executable(3.4_typechecker main.c)

target_link_libraries(3.4_typechecker 3.4_typechecker_lib)