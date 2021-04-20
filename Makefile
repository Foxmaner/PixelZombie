pixelzombie: main.o map.o
	gcc -o pixelzombie main.o map.o -lSDL2 -lSDL2_image
main.o: main.c

	gcc -c main.c

map.o: map.c
	gcc -c map.c

