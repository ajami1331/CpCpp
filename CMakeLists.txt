# CMakeList.txt : CMake project for CpCpp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12+)

project ("CpCpp")

# Define CLown1331
add_compile_definitions(CLown1331)

# Add source to this project's executable.
file(GLOB_RECURSE LIBRARY_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} library/*)
add_executable (${CMAKE_PROJECT_NAME} "CpCpp.cpp"  "utils.h" ${LIBRARY_SOURCES})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt  ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt  ${CMAKE_CURRENT_BINARY_DIR}/Debug/input.txt COPYONLY)

set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)
add_compile_definitions(STARTING_FILE="${CMAKE_CURRENT_SOURCE_DIR}/CpCpp.cpp")

# TODO: Add tests and install targets if needed.
