#ifndef udpClient_h
#define udpClient_h
#include <stdio.h>
#include <string.h>


void sendData(int flag, int x_cord, int y_cord, char selectedIp[100], int playerID);
void reciveData(char selectedIp[100], int kordinater[3]);
int reciveID(char selectedIp[100]);

#endif