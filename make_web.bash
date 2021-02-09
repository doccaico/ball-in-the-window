#!/bin/bash

# Info
# https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5)

CC=emcc

RAYLIB="$HOME/local/lib/raylib-3.5.0-wasm"

FLAGS="-DPLATFORM_WEB -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -Os"
FLAGS=" -I${RAYLIB}/src"
EMFLAGS="-s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 --shell-file shell.html"

# 1
CMD="${CC} -c ball-in-the-window.c -o ball-in-the-window.o ${FLAGS} ${EMFLAGS}"
${CMD}
echo ${CMD}

# 2
FLAGS+=" -s ${RAYLIB}/src/libraylib.a"
CMD="${CC} -o ball-in-the-window.html ball-in-the-window.o ${FLAGS} ${EMFLAGS}"
${CMD}
echo ${CMD}
