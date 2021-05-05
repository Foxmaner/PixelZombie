pixelzombie: main.o map.o zombie.o player.o udpClient.o gameInit.o gameRender.o gameMedia.o
	gcc -o pixelzombie main.o map.o zombie.o player.o udpClient.o gameInit.o gameRender.o gameMedia.o -lSDL2 -lSDL2_image -lSDL2_net
main.o: main.c
	gcc -c main.c
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
# add gameEvent
gameRender.o: gameRender.c
	gcc -c gameRender.c
gameMedia.o: gameMedia.c
	gcc -c gameMedia.c