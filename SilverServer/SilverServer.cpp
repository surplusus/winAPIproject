#include "SilverServer.h"
#include "Packet.h"
#include <Windows.h>
#include <iostream>
#include <stdexcept>

using namespace Gomoku;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::runtime_error;


namespace Gomoku {
	void CALLBACK RecvRoutine(DWORD dwError, DWORD szRecvBytes, LPWSAOVERLAPPED lpOverLapped, DWORD dwFlags);
	void CALLBACK SendRoutine(DWORD dwError, DWORD szRecvBytes, LPWSAOVERLAPPED lpOverLapped, DWORD dwFlags);
	
	Gomoku::SilverServer::SilverServer(const std::string & host, int port, int backlog) :
		host_(host), port_(port), backlog_(backlog), socket_(-1), isRunning_(true)
	{
	}

	void Gomoku::SilverServer::StartUp()
	{
		WSADATA wsadata;

		if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)	// not 0 means error!
		{
			string msg = "WSAStartup failed. (error code: " + to_string(WSAGetLastError()) + ")";
			cout << msg << endl;
			throw std::runtime_error(msg);
		}

		socket_ = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

		if (socket_ == INVALID_SOCKET)
		{
			string msg = "WSASocket failed. (error code: " + to_string(WSAGetLastError()) + ")";
			cout << msg << endl;
			throw std::runtime_error(msg);
		}

		u_long mode = 1;	// 0 : socket sealed // 1 : socket unsealed
		ioctlsocket(socket_, FIONBIO, &mode);

		SOCKADDR_IN severAddress = { 0 };	// handle of socket address
		severAddress.sin_family = AF_INET;
		//// cf) htons() : from host address(big-endian) to network address(little-endian)
		severAddress.sin_port = htons(port_);
		inet_pton(AF_INET, host_.c_str(), &severAddress.sin_addr.S_un.S_addr);

		if (bind(socket_, (LPSOCKADDR)&severAddress, sizeof(severAddress)) == SOCKET_ERROR)
		{
			string msg = "bind failed. (error code: " + to_string(WSAGetLastError()) + ")";
			cout << msg << endl;
			throw std::runtime_error(msg);
		}
		if (listen(socket_, backlog_) == SOCKET_ERROR)
		{
			string msg = "listen failed. (error code: " + to_string(WSAGetLastError()) + ")";
			cout << msg << endl;
			throw std::runtime_error(msg);
		}
	}

	void Gomoku::SilverServer::ShutDown()
	{
		closesocket(socket_);
		WSACleanup();
	}

	void Gomoku::SilverServer::Run()
	{
		SOCKET clientSocket = -1;
		SOCKADDR_IN clientAddress = { 0, };
		int clientAddressSize = sizeof(clientAddress);
		WSAOVERLAPPED* overlapped;
		Packet* packet;
		DWORD recvBytes, flags = 0;

#ifdef _DEBUG
		if (isRunning_ == true)
			cout << "Server Ready for Accept" << endl;
#endif // _DEBUG

		while (isRunning_)
		{
			SleepEx(300, TRUE);

			clientSocket = accept(socket_, (LPSOCKADDR)&clientAddress, &clientAddressSize);

			if (clientSocket == INVALID_SOCKET)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
					continue;
				else
				{
					string msg = "accept failed. (error code: " + to_string(WSAGetLastError()) + ")";
					cout << msg << endl;
					throw std::runtime_error(msg);
				}
			}

#ifdef _DEBUG
			cout << "Client (" << (int)socket_ << ") connect. . ." << endl;
#endif // _DEBUG

			overlapped = new WSAOVERLAPPED;
			memset(overlapped, 0, sizeof(WSAOVERLAPPED));

			packet = new Packet;
			packet->socket = clientSocket;
			packet->buffer.buf = new char[512];
			packet->buffer.len = 512;
			overlapped->hEvent = packet;
			WSARecv(clientSocket, &packet->buffer, 1, &recvBytes, &flags, overlapped, RecvRoutine);
		}
		closesocket(clientSocket);
	}

	void Gomoku::SilverServer::Stop()
	{
		isRunning_ = false;
	}

	void CALLBACK RecvRoutine(DWORD dwError, DWORD szRecvBytes, LPWSAOVERLAPPED lpOverLapped, DWORD dwFlags)
	{
		Packet* packet = (Packet*)lpOverLapped->hEvent;
		DWORD sentBytes;

		if (szRecvBytes == 0)
		{
			delete packet;
			delete lpOverLapped;
#ifdef _DEBUG
			cout << "Client disconnect. . ." << endl;
#endif // _DEBUG
		}
		else
		{
			// 데이터를 받았으니 무슨 처리를 한다
			// 오목 게임 룰 연산을 담당한다
			cout << packet->buffer.buf << endl;
			WSASend(packet->socket, &packet->buffer, 1, &sentBytes, 0, lpOverLapped, SendRoutine);
		}
	}

	void CALLBACK SendRoutine(DWORD dwError, DWORD szRecvBytes, LPWSAOVERLAPPED lpOverLapped, DWORD dwFlags)
	{
		Packet* packet = (Packet*)lpOverLapped->hEvent;
		DWORD recvBytes, flags = 0;
		WSARecv(packet->socket, &packet->buffer, 1, &recvBytes, &flags, lpOverLapped, RecvRoutine);
	}
}
