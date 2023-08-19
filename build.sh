#!/bin/bash

if [ ! -d ./bin ];
then
	mkdir bin
fi

gcc -Wall -Wextra src/main.c -o bin/minesweeper
