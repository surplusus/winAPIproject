#include "Packet.h"



Gomoku::Packet::Packet() : socket(-1)
{
}


Gomoku::Packet::~Packet()
{
	closesocket(socket);
	delete buffer.buf;
}
