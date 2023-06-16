cmake_minimum_required(VERSION 3.16)
set(CMAKE_C_COMPILER "gcc")

project(address_book LANGUAGES C)

# Specify the source files for the library that are in the lib directory.
file(GLOB linkedlist_SOURCES "lib/*.c")

# Create a library called linkedlist from the specified source files.
add_library(linkedlist SHARED
  ${linkedlist_SOURCES}
)

# Set the output directory for the library
set_target_properties(linkedlist PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

file(GLOB APP_SOURCES "src/*.c")

# Compile the address_book binary
add_executable(address_book
  ${APP_SOURCES}
)

# Link the address_book binary with the linkedlist library
target_link_libraries(address_book linkedlist)

# Set the output directory for the binary
set_target_properties(address_book PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
