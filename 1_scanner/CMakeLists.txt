cmake_minimum_required(VERSION 3.15)
# cmake_minimum_required(VERSION 2.8)

project(kpl_scanner VERSION 1.0.1 DESCRIPTION "KPL scanner")

add_library(kpl_scanner SHARED
    charcode.c
    error.c
    reader.c
    token.c
)

set_target_properties(kpl_scanner PROPERTIES 
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

add_executable(scanner scanner.c)

target_link_libraries(scanner kpl_scanner)

# set(
#     SOURCE
#     charcode.c
#     error.c
#     reader.c
#     token.c
#     scanner.c 
# )

# add_executable(scanner ${SOURCE})