pixelzombie: main.o map.o zombie.o
	gcc -o pixelzombie main.o map.o zombie.o -lSDL2 -lSDL2_image
main.o: main.c
	gcc -c main.c
map.o: map.c
	gcc -c map.c
zombie.o: zombie.c
	gcc -c zombie.c
