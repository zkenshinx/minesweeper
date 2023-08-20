#!/bin/bash

if [ ! -d ./bin ];
then
	mkdir bin
fi

gcc -Wall -Wextra src/main.c src/grid.c -lSDL2 -o bin/minesweeper
