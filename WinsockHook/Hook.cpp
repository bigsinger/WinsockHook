#include <windows.h>
#include <stdio.h>
#include "Util\Common.h"
#include "Util\Hook.h"

bool bLogRecv = false;
bool bLogSend = false;

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
		printf("[Recv-%d:%d] ", length, flags);
		util::Log("[Recv-%d:%d] ", length, flags);
		for (int i = 0; i < length; i++)
		{
			printf("%02X ", (unsigned char)buffer[i]);
			util::Log("%02X ", (unsigned char)buffer[i]);
		}
		printf("\n");
		util::Log("\n");
	}

	return precv(socket, buffer, length, flags);
}

int WINAPI MyRecvfrom(SOCKET socket, char* buffer, int length, int flags, sockaddr* from, int* fromlen) {
	if (mySock == 0) {
		util::Log("[SOCKET - %d]", socket);
		mySock = socket;
	}

	if (bLogRecv && length > MINPACKETLEN) {
		printf("[Recv-%d:%d] ", length, flags);
		util::Log("[Recv-%d:%d] ", length, flags);
		for (int i = 0; i < length; i++) {
			printf("%02X ", (unsigned char)buffer[i]);
			util::Log("%02X ", (unsigned char)buffer[i]);
		}
		printf("\n");
		util::Log("\n");
	}

	return precv(socket, buffer, length, flags);
}


int WINAPI MySend(SOCKET socket, const char* buffer, int length, int flags)
{
	if (mySock == 0) {
		util::Log("[SOCKET - %d]\n", socket);
		mySock = socket;
	}

	if (bLogSend && length > MINPACKETLEN)
	{
		printf("[Send-%d:%d] ", length, flags);
		util::Log("[Send-%d:%d] ", length, flags);
		for (int i = 0; i < length; i++)
		{
			printf("%02X ", (unsigned char)buffer[i]);
			util::Log("%02X ", (unsigned char)buffer[i]);
		}
		printf("\n");
		util::Log("\n");
	}
	return psend(socket, buffer, length, flags);
}

int WINAPI MySendto(SOCKET socket, const char* buffer, int length, int flags, const sockaddr* to, int tolen) {
	if (mySock == 0) {
		util::Log("[SOCKET - %d]\n", socket);
		mySock = socket;
	}

	if (bLogSend && length > MINPACKETLEN) {
		printf("[Send-%d:%d] ", length, flags);
		util::Log("[Send-%d:%d] ", length, flags);
		for (int i = 0; i < length; i++) {
			printf("%02X ", (unsigned char)buffer[i]);
			util::Log("%02X ", (unsigned char)buffer[i]);
		}
		printf("\n");
		util::Log("\n");
	}
	return psend(socket, buffer, length, flags);
}
