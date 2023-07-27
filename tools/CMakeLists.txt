cmake_minimum_required (VERSION 3.12+)

project ("tools")

# Add source to this project's executable.
add_executable (tools_book-generator book-generator.cpp)
add_compile_definitions(TOOLS_BOOK_GENERATOR_OUT_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../public/")

set_property(TARGET tools_book-generator PROPERTY CXX_STANDARD 17)

# TODO: Add tests and install targets if needed.
