cmake_minimum_required(VERSION 3.15)

project(1_scanner VERSION 1.0.1 DESCRIPTION "KPL scanner")

# set( Boost_LIBRARY_DIR /usr/bin )

# SHARED LIBRARY
add_library(1_scanner 
# SHARED
STATIC
# OBJECT
    charcode.c
    error.c
    reader.c
    token.c
    charcode.h
    error.h
    reader.h
    token.h
)
target_include_directories(1_scanner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_link_libraries ( 1_scanner 
# -pthread 
# ${Boost_LIBRARIES} )
set_target_properties(1_scanner PROPERTIES 
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)
# set ( PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR} )
# include_directories ( "${PROJECT_INCLUDE_DIR}" )


add_executable(scanner scanner.c)
target_link_libraries(scanner PRIVATE 1_scanner)
# set(
#     SOURCE
#     charcode.c
#     error.c
#     reader.c
#     token.c
#     scanner.c 
# )

# add_executable(scanner ${SOURCE})
