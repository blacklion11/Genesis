

CC=gcc
LDFLAGS=-lncurses
CCFLAGS=

main: main.c gamemanager.c input.c utils.c graphicsmanager.c playermanager.c worldmanager.c cameramanager.c
	gcc $(LDFLAGS) main.c gamemanager.c input.c utils.c graphicsmanager.c playermanager.c worldmanager.c cameramanager.c -o run
