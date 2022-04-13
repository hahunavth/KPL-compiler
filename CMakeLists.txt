project(kpl_scanner)

cmake_minimum_required(VERSION 2.8)

# add_library(mylib 
#     charcode.c
#     error.c
#     reader.c
#     token.c
# )

set(
    SOURCE
    charcode.c
    error.c
    reader.c
    token.c
    scanner.c 
)

add_executable(scanner ${SOURCE})