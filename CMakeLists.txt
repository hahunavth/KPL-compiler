cmake_minimum_required(VERSION 3.15)
# project(kpi_compiler VERSION 0.1.0)
project(kpi NONE)

include(CTest)
enable_testing()

# set(CMAKE_C_COMPILER_WORKS 1)
# set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
# set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

# #Include headers
# get_filename_component(PARENT_DIR ../ ABSOLUTE)
# include_directories(${PARENT_DIR}/1_scanner)
# include_directories(${PARENT_DIR}/1.2_scanner)

set ( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build )

set ( PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include )

# Subprojects
add_subdirectory(1_scanner)
add_subdirectory(1b_scanner)
add_subdirectory(3.1_symtab)
add_subdirectory(3.2_symtab)
add_subdirectory(3.3_semantic)
# add_subdirectory(2_parser)

# target_link_libraries(scanner ${PROJECT_NAME}_1_scanner)
# target_link_libraries(scanner kpl_scanner)

