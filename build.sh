#!/bin/bash

if [ ! -d ./bin ];
then
	mkdir bin
fi

gcc -Wall -Wextra src/main.c src/grid.c -o bin/minesweeper
