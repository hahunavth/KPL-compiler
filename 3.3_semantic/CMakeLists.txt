cmake_minimum_required(VERSION 3.15)

project(
    3.3_semantic
    VERSION 1.0.1
    DESCRIPTION
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(3.3_semantic_lib STATIC
    debug.c
    symtab.c
    debug.h
    symtab.h
    parser.c
    charcode.c
    error.c
    reader.c
    token.c
    scanner.c
    main.c
    semantics.c
)
target_include_directories(3.3_semantic_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(3.3_semantic_lib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

add_executable(3.3_semantic main.c)

target_link_libraries(3.3_semantic 3.3_semantic_lib)
