pixelzombie: main.o
	gcc -o pixelzombie main.o -lSDL2 -lSDL2_image
main.o: main.c
	gcc -c main.c