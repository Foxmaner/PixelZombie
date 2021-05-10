pixelzombie: main.o menu.o map.o zombie.o player.o udpClient.o gameInit.o gameEvent.o gameRender.o gameMedia.o 
	gcc -o pixelzombie main.o menu.o map.o zombie.o player.o udpClient.o gameInit.o gameEvent.o gameRender.o gameMedia.o -lSDL2 -lSDL2_image -lSDL2_net -lSDL2_mixer
main.o: main.c
	gcc -c main.c
menu.o: menu.c
	gcc -c menu.c
map.o: map.c
	gcc -c map.c
zombie.o: zombie.c
	gcc -c zombie.c
player.o: player.c
	gcc -c player.c
udpClient.o: server/udpClient.c
	gcc -c server/udpClient.c
gameInit.o: gameInit.c
	gcc -c gameInit.c
gameEvent.o: gameEvent.c
	gcc -c gameEvent.c
gameRender.o: gameRender.c
	gcc -c gameRender.c
gameMedia.o: gameMedia.c
	gcc -c gameMedia.c
