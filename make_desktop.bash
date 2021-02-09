#!/bin/bash

CC=gcc

RAYLIB="$HOME/local/lib/raylib-3.5.0-desktop"

FLAGS="-Wall -std=c99"
FLAGS+=" -I${RAYLIB}/include"
FLAGS+=" -L${RAYLIB}/lib"
FLAGS+=" -Wl,-rpath=${RAYLIB}/lib"

LIBS="-lraylib"

CMD="${CC} ${FLAGS} ball-in-the-window.c -o ball-in-the-window ${LIBS}"
${CMD}
echo ${CMD}
