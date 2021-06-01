pixelzombie: main.o menu.o ttf.o map.o zombie.o player.o udpClient.o gameInit.o gameEvent.o gameRender.o gameMedia.o gameQuit.o
	gcc -o pixelzombie main.o ttf.o menu.o map.o zombie.o player.o udpClient.o gameInit.o gameEvent.o gameRender.o gameMedia.o gameQuit.o -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lSDL2_mixer -lSDL2_ttf
main.o: main.c
	gcc -c main.c
menu.o: lib/src/menu.c
	gcc -c lib/src/menu.c
ttf.o: lib/src/ttf.c 
	gcc -c lib/src/ttf.c
map.o: lib/src/map.c
	gcc -c lib/src/map.c
zombie.o: lib/src/zombie.c
	gcc -c lib/src/zombie.c
player.o: lib/src/player.c
	gcc -c lib/src/player.c
udpClient.o: server/udpClient.c
	gcc -c server/udpClient.c
gameInit.o: lib/src/gameInit.c
	gcc -c lib/src/gameInit.c
gameEvent.o: lib/src/gameEvent.c
	gcc -c lib/src/gameEvent.c
gameRender.o: lib/src/gameRender.c
	gcc -c lib/src/gameRender.c
gameMedia.o: lib/src/gameMedia.c
	gcc -c lib/src/gameMedia.c
gameQuit.o: lib/src/gameQuit.c
	gcc -c lib/src/gameQuit.c