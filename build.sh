#!/bin/bash

# Exit on error
set -e

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Configure with CMake
cmake ..

# Build using all available cores
cmake --build . -j$(nproc)

# Return to original directory
cd ..
