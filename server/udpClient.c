#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "udpClient.h"
#include "SDL2/SDL_net.h"
 
void sendData(int data)
{
    int x_pos = 1;
    int y_pos = 1;

    UDPsocket sd;
	IPaddress srvadd;
	UDPpacket *p;
    UDPpacket *p2;

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
		fprintf(stderr, "SDLNet_ResolveHost(192.0.0.1 2000): %s\n", SDLNet_GetError());
		//exit(EXIT_FAILURE);
	}

    if (!((p = SDLNet_AllocPacket(512))&& (p2 = SDLNet_AllocPacket(512))))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		//exit(EXIT_FAILURE);
	}


            // send and retrive positions  
        
            
            sprintf((char *)p->data, "%d %d\n", (int) x_pos, (int) y_pos);    
            p->address.host = srvadd.host;	/* Set the destination host */
		    p->address.port = srvadd.port;	/* And destination port */
		    p->len = strlen((char *)p->data) + 1;
            SDLNet_UDP_Send(sd, -1, p);

             
        
} 
