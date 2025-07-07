#!/bin/bash

set -e  # Exit immediately if a command exits with a non-zero status

# Step 1: Create and enter the build directory
mkdir -p build
cd build

# Step 2: Run CMake to configure the project
cmake ..

# Step 3: Compile the project using all available CPU cores
make -j$(nproc)

# Step 4: Run the test executable
echo -e "\nRunning the tests \n"
ctest --output-on-failure
