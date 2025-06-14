cmake_minimum_required(VERSION 3.10)
project(DiscountSystem)

set(CMAKE_CXX_STANDARD 17)

# Enable testing
enable_testing()

# Add Abseil
find_package(absl REQUIRED)

# Collect header files
file(GLOB_RECURSE HEADER_FILES 
    "src/*.h"
)

# Add source files
add_library(discount_lib INTERFACE ${HEADER_FILES})

# Set include directories
target_include_directories(discount_lib INTERFACE ${CMAKE_SOURCE_DIR})

# Add tests
add_subdirectory(test)
