#!/bin/bash

# Set the project directory (use the current directory)
PROJECT_DIR=$(pwd)

# Find all .cpp and .h files
CPP_FILES=$(find $PROJECT_DIR -type f -name "*.cpp")
H_FILES=$(find $PROJECT_DIR -type f -name "*.h")

ASSETS_PATH=$(pwd)/web/

# Print out the files being compiled (for debugging purposes)
echo "Compiling the following .cpp files:"
echo "$CPP_FILES"

# If needed, set additional compiler flags here
COMPILER_FLAGS="-s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS=["png"] -s USE_SDL_MIXER=2 -s USE_SDL_TTF=2"

# Compile the files
emcc -O3 $CPP_FILES $COMPILER_FLAGS -o index.js

echo "Compilation complete."


