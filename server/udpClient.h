#ifndef udpClient_h
#define udpClient_h
#include <stdio.h>
#include <string.h>

//Creates a packet to send to the server 
void sendData(int flag, int x_cord, int y_cord, char selectedIp[100], int playerID);

//Recives data packet from the server
void reciveData(char selectedIp[100], int kordinater[4]);

//Gets the main users ID
int reciveID(char selectedIp[100]);

#endif