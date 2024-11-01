#!/bin/bash
# Check if we have an input file
if [ $# -lt 1 ]; then
    echo "Usage: ./run.sh <input_file.pst> [options]"
    exit 1
fi

# Get absolute path of input file
INPUT_FILE=$(realpath "$1")
shift

# Change to build directory
cd build || { echo "Error: build directory not found"; exit 1; }

# Run pryst with input file and remaining arguments
./pryst "$INPUT_FILE" "$@"
