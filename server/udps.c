#if 0
#!/bin/sh
gcc -Wall `sdl-config --cflags` udps.c -o udps `sdl-config --libs` -lSDL_net
 
exit
#endif
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "SDL2/SDL_net.h"
 
int WinMain(int argc, char **argv)
{
	UDPsocket sd;       /* Socket descriptor */
	UDPpacket *pRecive;       /* Pointer to packet memory */
	UDPpacket *pSent;
    Uint32 IPclient[4]={0}; 
    Uint32 IPclient2=0;
    Uint32 portClient[4]={0}; 
    Uint32 portClient2=0;
    int quit, a, b;
	int nrOfConnections = 0;
 
	/* Initialize SDL_net */
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	/* Open a socket */
	if (!(sd = SDLNet_UDP_Open(2000)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	/* Make space for the packet */
	if (!((pSent = SDLNet_AllocPacket(512))&&(pRecive = SDLNet_AllocPacket(512))))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	/* Main loop */
	quit = 0;
	while (!quit)
	{
		/* Wait a packet. UDP_Recv returns != 0 if a packet is coming */
		if (SDLNet_UDP_Recv(sd, pRecive))
		{
			printf("UDP Packet incoming\n");
			printf("\tData:    %s\n", (char *)pRecive->data);
			printf("\tAddress: %x %x\n", pRecive->address.host, pRecive->address.port);
            if(IPclient[0] == 0 && portClient[0] == 0){
                printf("Client 1\n");
                IPclient[0] = pRecive->address.host;
                portClient[0] = pRecive->address.port;
				nrOfConnections =1;
            }else if(pRecive->address.port != portClient[0]  && IPclient[1] == 0){
                printf("Client 2\n");
                IPclient[1] = pRecive->address.host;
                portClient[1] = pRecive->address.port;
				nrOfConnections =2;
            }else if(pRecive->address.port != portClient[0] && pRecive->address.port != portClient[1]  && IPclient[2] == 0){
                printf("Client 3\n");
                IPclient[2] = pRecive->address.host;
                portClient[2] = pRecive->address.port;
				nrOfConnections = 3;
            }else if(pRecive->address.port != portClient[0] && pRecive->address.port != portClient[1] && pRecive->address.port != portClient[2] && IPclient[3] == 0){
                printf("Client 4\n");
                IPclient[3] = pRecive->address.host;
                portClient[3] = pRecive->address.port;
				nrOfConnections =4;
            }

		if(nrOfConnections > 0){
			//printf("ELSE?\n");
			//printf("Port %x ---", pRecive->address.port);
			//printf("Port %x ---", portClient[0]);
			for(int i=0; i < nrOfConnections; i++){
				if (pRecive->address.port == portClient[i]){
					printf("Recived data %d\n", i);
					for(int j=0; j < nrOfConnections; j++){
						printf("TESTFORLOOP %d %d\n", j, nrOfConnections);
						if(IPclient[j] != 0){
							if(i != j){
								printf("Send to Client %d\n", j);
								pSent->address.host = IPclient[j];	/* Set the destination host */
								pSent->address.port = portClient[j];
								sscanf((char * )pRecive->data, "%d %d", &a, &b);
								printf("%d %d %d\n", i, a, b);
								sprintf((char *)pSent->data, "%d %d %d\n", i, a, b);
								pSent->len = strlen((char *)pSent->data) + 1;
								SDLNet_UDP_Send(sd, -1, pSent);
							}
						}
					}
				} 
			}
			
		}
            

			/* Quit if packet contains "quit" */
			if (strcmp((char *)pSent->data, "quit") == 0)
				quit = 1;
		}		
	}
 
	/* Clean and exit */
	SDLNet_FreePacket(pSent);
    SDLNet_FreePacket(pRecive);
	SDLNet_Quit();
	return EXIT_SUCCESS;
} 
