

CC=gcc
LDFLAGS=-lncurses
CCFLAGS=

main: main.c gamemanager.c input.c utils.c graphicsmanager.c playermanager.c worldmanager.c
	gcc $(LDFLAGS) main.c gamemanager.c input.c utils.c graphicsmanager.c playermanager.c worldmanager.c -o run
