#include <windows.h>
#include <stdio.h>
#include "Util\Common.h"
#include "Util\Hook.h"

bool bLogRecv = false;
bool bLogSend = false;
bool bRunning = false;

SOCKET mySock = 0;
int (WINAPI *precv)(SOCKET socket, char* buffer, int length, int flags) = NULL;
int (WINAPI* precvfrom)(SOCKET socket, char* buffer, int length, int flags, sockaddr* from, int* fromlen);
int (WINAPI *psend)(SOCKET socket, const char* buffer, int length, int flags) = NULL;
int (WINAPI* psendto)(SOCKET socket, const char* buffer, int length, int flags, const sockaddr* to, int            tolen);


int WINAPI MyRecv(SOCKET socket, char* buffer, int length, int flags)
{
	if (mySock == 0) {
		util::Log("[SOCKET - %d]", socket);
		mySock = socket;
	}

	if (bLogRecv && length > MINPACKETLEN) {
		char msg[MAXPACKETLEN];
		int size = length >= MAXPACKETLEN ? MAXPACKETLEN - 2 : length;
		memcpy(msg, buffer, size);
		msg[size] = '\0';
		util::Log("[Winsock]recv socket: %d len: %d buffer: %s\n", socket, length, msg);
	}

	return precv(socket, buffer, length, flags);
}

int WINAPI MyRecvfrom(SOCKET socket, char* buffer, int length, int flags, sockaddr* from, int* fromlen) {
	if (mySock == 0) {
		util::Log("[SOCKET - %d]", socket);
		mySock = socket;
	}

	if (bLogRecv && length > MINPACKETLEN) {
		char msg[MAXPACKETLEN];
		int size = length >= MAXPACKETLEN ? MAXPACKETLEN -2 : length;
		memcpy(msg, buffer, size);
		msg[size] = '\0';
		util::Log("[Winsock]recvfrom socket: %d len: %d buffer: %s\n", socket, length, msg);
	}

	return precvfrom(socket, buffer, length, flags, from, fromlen);
}


int WINAPI MySend(SOCKET socket, const char* buffer, int length, int flags) {
	if (mySock == 0) {
		util::Log("[SOCKET - %d]\n", socket);
		mySock = socket;
	}

	if (bLogSend && length > MINPACKETLEN) {
		char msg[MAXPACKETLEN];
		int size = length >= MAXPACKETLEN ? MAXPACKETLEN - 2 : length;
		memcpy(msg, buffer, size);
		msg[size] = '\0';
		util::Log("[Winsock]send socket: %d len: %d buffer: %s\n", socket, length, msg);
	}
	return psend(socket, buffer, length, flags);
}

int WINAPI MySendto(SOCKET socket, const char* buffer, int length, int flags, const sockaddr* to, int tolen) {
	if (mySock == 0) {
		util::Log("[SOCKET - %d]\n", socket);
		mySock = socket;
	}

	if (bLogSend && length > MINPACKETLEN) {
		char msg[MAXPACKETLEN];
		int size = length >= MAXPACKETLEN ? MAXPACKETLEN - 2 : length;
		memcpy(msg, buffer, size);
		msg[size] = '\0';
		util::Log("[Winsock]sendto socket: %d len: %d buffer: %s\n", socket, length, msg);
	}
	return psendto(socket, buffer, length, flags, to, tolen);
}
