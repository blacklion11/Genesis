

CC=gcc
LDFLAGS=-lncurses
CCFLAGS=

main: main.c gamemanager.c input.c utils.c graphicsmanager.c
	gcc $(LDFLAGS) main.c gamemanager.c input.c utils.c graphicsmanager.c -o run
