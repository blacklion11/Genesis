

CC=gcc
LDFLAGS=-lncurses
CCFLAGS=

main: main.c gamemanager.c input.c
	gcc $(LDFLAGS) main.c gamemanager.c input.c -o run
