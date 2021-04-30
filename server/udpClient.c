#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "udpClient.h"
#include "SDL2/SDL_net.h"

UDPsocket sd;
IPaddress srvadd;
UDPpacket *p;
UDPpacket *p2;

void createConnection(char selectedIp[100])
{

	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		//exit(EXIT_FAILURE);
	}

	if (!(sd = SDLNet_UDP_Open(0)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		//exit(EXIT_FAILURE);
	}

	/* Resolve server name  */
	if (SDLNet_ResolveHost(&srvadd, "127.0.0.1", 2000) == -1)
	{
		fprintf(stderr, "SDLNet_ResolveHost(81.230.227.193 2000) : % s\n ", SDLNet_GetError());
		//exit(EXIT_FAILURE);
	}
}

void sendData(int x_cord, int y_cord, char selectedIp[100])
{

	if (sd != NULL){
		if (!((p = SDLNet_AllocPacket(512)) && (p2 = SDLNet_AllocPacket(512))))
		{
			fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
			//exit(EXIT_FAILURE);
		}

		// send and retrive positions

		sprintf((char *)p->data, "%d %d\n", (int)x_cord, (int)y_cord);
		p->address.host = srvadd.host; /* Set the destination host */
		p->address.port = srvadd.port; /* And destination port */
		p->len = strlen((char *)p->data) + 1;
		SDLNet_UDP_Send(sd, -1, p);

		
	}
	else{
		createConnection(selectedIp);
		sendData(x_cord, y_cord, selectedIp);
	}
}

void reciveData(char selectedIp[100], int kordinater[2]){
	if (sd != NULL){
		if (SDLNet_UDP_Recv(sd, p2)){
			int i, a, b;
			sscanf((char *)p2->data, "%d %d %d", &i, &a, &b);
			
			printf("Balle UDP Packet incoming %d %d %d\n", i, a, b);
			kordinater[0] = a;
			kordinater[1] = b;
			
		}
		else{
			kordinater[0] = -1000;
			kordinater[1] = -1000;
		}
	}
	else{
		createConnection(selectedIp);
		reciveData(selectedIp, kordinater);
	}
	
}