#!/bin/bash

if [ ! -d ./bin ];
then
	mkdir bin
fi

gcc -Wall -Wextra src/main.c src/grid.c src/textures.c -lSDL2 -lSDL2_image -o bin/minesweeper
