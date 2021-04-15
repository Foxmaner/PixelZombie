pixelzombie: main.o gridSystem.o
	gcc -o pixelzombie main.o gridSystem.o -lSDL2 -lSDL2_image
main.o: main.c
	gcc -c main.c
gridSystem.o: gridSystem.c
	gcc -c gridSystem.c