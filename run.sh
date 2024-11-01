#!/bin/bash
# Check if we have an input file
if [ $# -lt 1 ]; then
    echo "Usage: ./run.sh <input_file.pst> [options]"
    exit 1
fi

# Change to build directory
cd build || { echo "Error: build directory not found"; exit 1; }

# Run pryst with all provided arguments
./pryst "$@"
