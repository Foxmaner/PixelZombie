#ifndef udpClient_h
#define udpClient_h
#include <stdio.h>
#include <string.h>


void sendData(int x_cord, int y_cord, char selectedIp[100]);
void reciveData(char selectedIp[100], int kordinater[2]);
int reciveID(char selectedIp[100]);

#endif