cmake_minimum_required(VERSION 3.15)

project(2c_parser_completed VERSION 1.0.1 DESCRIPTION "KPL parser completed")
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