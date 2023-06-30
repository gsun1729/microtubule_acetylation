#!/bin/bash

# Check if a directory name was provided
if [ $# -eq 0 ]; then
    echo "No directory name provided. Using 'build' as default."
    dir_name="build"
else
    dir_name=$1
fi

# Create the directory and build the project
mkdir -p $dir_name
cd $dir_name
cmake ..
make


bin/output
