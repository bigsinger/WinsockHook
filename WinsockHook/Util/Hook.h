#pragma once
#include <winsock.h>

#define MINPACKETLEN 0
#define MAXPACKETLEN 5000

extern SOCKET mySock;
extern bool bLogRecv;
extern bool bLogSend;
extern bool bRunning;

// HOOKS

// winsock recv
extern int (WINAPI *precv)(SOCKET socket, char* buffer, int length, int flags);
int WINAPI MyRecv(SOCKET socket, char* buffer, int length, int flags);

// winsock recvfrom
extern int (WINAPI* precvfrom)(SOCKET socket, char* buffer, int length, int flags, sockaddr* from, int* fromlen);
int WINAPI MyRecvfrom(SOCKET socket, char* buffer, int length, int flags, sockaddr* from, int* fromlen);

// winsock send
extern int (WINAPI *psend)(SOCKET socket, const char* buffer, int length, int flags);
int WINAPI MySend(SOCKET socket, const char* buffer, int length, int flags);


// winsock sendto
extern int (WINAPI* psendto)(SOCKET socket, const char* buffer, int length, int flags, const sockaddr* to, int            tolen);
int WINAPI MySendto(SOCKET socket, const char* buffer, int length, int flags, const sockaddr* to, int tolen);