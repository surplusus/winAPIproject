#pragma once
#include <WinSock2.h>
typedef struct Packet
{
	SOCKET socket;
	WSABUF buffer;

	Packet();
	~Packet();
} PACKET;
