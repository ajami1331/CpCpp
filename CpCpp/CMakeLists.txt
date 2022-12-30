# CMakeList.txt : CMake project for CpCpp, include source and define
# project specific logic here.
#

# Define CLown1331
add_compile_definitions(CLown1331)

# Add source to this project's executable.
add_executable (CpCpp "CpCpp.cpp"  "utils.h" "library/DisjointSet.h" "solution.h")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt  ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CpCpp PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
