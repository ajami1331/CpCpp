﻿# CMakeList.txt : CMake project for CpCpp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12+)

project ("CpCpp")

# Define CLown1331
add_compile_definitions(CLown1331)

# Add source to this project's executable.
file(GLOB_RECURSE LIBRARY_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} library/*)
add_executable (${CMAKE_PROJECT_NAME} "CpCpp.cpp"  "utils.h" ${LIBRARY_SOURCES})

set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 17)
add_compile_definitions(STARTING_FILE="${CMAKE_CURRENT_SOURCE_DIR}/CpCpp.cpp")
add_compile_definitions(INPUT_FILE="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
add_compile_definitions(OUTPUT_FILE="${CMAKE_CURRENT_SOURCE_DIR}/output.txt")
add_compile_definitions(VALID_FILE="${CMAKE_CURRENT_SOURCE_DIR}/valid.txt")
add_compile_definitions(TEST_CASES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test_cases/")
add_compile_definitions(CP_LIBRARY_PATH="${CMAKE_CURRENT_SOURCE_DIR}/library/")

if (NOT MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic 
    -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op 
    -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align 
    -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 
    -fsanitize=address -fsanitize=undefined -fno-sanitize-recover 
    -fstack-protector)
    target_link_libraries(${PROJECT_NAME} -lasan -lubsan)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
endif()

add_subdirectory(tools)

# TODO: Add tests and install targets if needed.
