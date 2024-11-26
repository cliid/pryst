#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <input.pst>"
    exit 1
fi

# Get the absolute path of the input file
INPUT_FILE=$(realpath "$1")

# Change to the directory containing the script
cd "$(dirname "$0")"

# Run the compiler with the input file
./build/pryst "$INPUT_FILE"
