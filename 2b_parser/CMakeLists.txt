cmake_minimum_required(VERSION 3.15)

project(2b_parser VERSION 1.0.1 DESCRIPTION "KPL parser")
enable_testing()


add_executable(parser parser.c
    ../2_parser/charcode.c
    ../2_parser/error.c
    ../2_parser/reader.c
    ../2_parser/token.c
    ../2_parser/scanner.c
    ../2_parser/main.c
)

include_directories( ../2_parser)


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