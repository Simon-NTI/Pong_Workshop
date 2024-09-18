#!/bin/sh
rm YourGame
cc "main.c" $(pkg-config --libs --cflags raylib) -o "YourGame"
./YourGame