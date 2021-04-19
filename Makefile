pixelzombie: main.o
	gcc -o pixelzombie main.o map.o -lSDL2 -lSDL2_image
main.o: main.c
	gcc -c main.c

world.o: map.c
	gcc -c map.c
