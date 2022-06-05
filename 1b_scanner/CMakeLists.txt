cmake_minimum_required(VERSION 3.15)

project(scanner_2
 VERSION 1.0.1 
 DESCRIPTION "KPL scanner extends"
)

add_executable(scanner_2 scanner.c)
target_link_libraries(scanner_2 1_scanner)

