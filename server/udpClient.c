#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "udpClient.h"
#include "SDL2/SDL_net.h"

UDPsocket sd;
IPaddress srvadd;
UDPpacket *p;
UDPpacket *p2;
int playerID;


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
		fprintf(stderr, "SDLNet_ResolveHost(81.230.227.193 Detta är eskils ip ba fuck han 2000) : % s\n ", SDLNet_GetError());
		//exit(EXIT_FAILURE);
	}
}

void sendData(int flag, int x_cord, int y_cord, char selectedIp[100], int playerID)
{

	if (sd != NULL){
		if (!((p = SDLNet_AllocPacket(512)) && (p2 = SDLNet_AllocPacket(512))))
		{
			fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
			//exit(EXIT_FAILURE);
		}

		// send and retrive positions

		sprintf((char *)p->data, "%d %d %d %d\n", (int)flag, (int)playerID, (int)x_cord, (int)y_cord);
		p->address.host = srvadd.host; /* Set the destination host */
		p->address.port = srvadd.port; /* And destination port */
		p->len = strlen((char *)p->data) + 1;
		SDLNet_UDP_Send(sd, -1, p);

		
	}
	else{
		createConnection(selectedIp);
		sendData(flag, x_cord, y_cord, selectedIp,playerID);
	}
}

void reciveData(char selectedIp[100], int kordinater[3]){
	if (sd != NULL){
		if (SDLNet_UDP_Recv(sd, p2)){
			int flag, recivedID, a, b;
			sscanf((char *)p2->data, "%d %d %d %d", &flag, &recivedID, &a, &b);

			printf("UDP Packet incoming %d %d %d %d\n", flag, recivedID, a, b);
			//Flag = 0 == Player reporting possition
			//Flag = 1 == Player reporting gunshot
			//Flag = 2 == Player reporting zombieDeath
			if(flag == 0){
				kordinater[0] = recivedID;
				kordinater[1] = a;
				kordinater[2] = b;
			}else if(flag == 1){
				printf("Skott avfyrades av spelare: %d ", recivedID);
			}
			
			
		}
		else{
			kordinater[0] = -1000;
			kordinater[1] = -1000;
			kordinater[2] = -1000;
		}
	}
	else{
		createConnection(selectedIp);
		reciveData(selectedIp, kordinater);
	}
	
}

int reciveID(char selectedIp[100]){
	if (sd != NULL){
		if (SDLNet_UDP_Recv(sd, p2)){
			int i;
			sscanf((char *)p2->data, "%d", &i);
			printf("UDP Packet incoming with ID %d\n", i);
			return i;
		}
		else{
			//printf("Inget id Mottaget! \n");
		}
	}
	else{
		printf("SD = null");
		createConnection(selectedIp);
		reciveID(selectedIp);
	}
	return -1;
	
}