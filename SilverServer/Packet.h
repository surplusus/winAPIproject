#pragma once
#include <WinSock2.h>
namespace Gomoku {
	struct Packet
	{
		SOCKET socket;
		WSABUF buffer;

		Packet();
		~Packet();
	};


}
