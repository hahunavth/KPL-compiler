# cmake_minimum_required(VERSION 3.15)

# project(2_parser VERSION 1.0.1 DESCRIPTION "KPL parser")

# # SHARED LIBRARY
# add_library(2_parser
# STATIC
#     charcode.c
#     error.c
#     reader.c
#     token.c
#     scanner.c
#     charcode.h
#     error.h
#     reader.h
#     token.h
#     scanner.h
# )

# target_include_directories(2_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# set_target_properties(2_parser PROPERTIES
#     VERSION ${PROJECT_VERSION}
#     SOVERSION 1
# )

# add_executable(parser parser.c)
# target_link_libraries(parser PRIVATE 2_parser)


cmake_minimum_required(VERSION 3.15)

project(2_parser VERSION 1.0.1 DESCRIPTION "KPL parser")
enable_testing()
add_executable(parser parser.c
    charcode.c
    error.c
    reader.c
    token.c
    scanner.c
    main.c
)

add_test(NAME parser_example3
         COMMAND parser ../Test/example3.kpl)
add_test(NAME parser_example2
         COMMAND parser ../Test/example2.kpl)
add_test(NAME parser_example1
         COMMAND parser ../Test/example1.kpl)

add_test(NAME parser_sum
         COMMAND parser ../Test/sum.kpl)

add_test(NAME parser_assignment1
         COMMAND parser ../Test/Assignment1.kpl)