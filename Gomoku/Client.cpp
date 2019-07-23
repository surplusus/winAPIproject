#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "stdafx.h"
#include "Client.h"
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::runtime_error;
// 설마 여기서 바로 수정할수 있는건가....대박박!!!
Gomoku::Client::Client(const std::string & host, int port) : 
	host_(host), port_(port), Socket_(-1), isRunning_(true)
{
}

void Gomoku::Client::Connect()
{
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		string msg = "WSAStartup failed. (error code : " + to_string(WSAGetLastError()) + ")";
		cout << msg << endl;
		throw runtime_error(msg);
	}

	Socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Socket_ == INVALID_SOCKET)
	{
		string msg = "socket failed. (error code : " + to_string(WSAGetLastError()) + ")";
		cout << msg << endl;
		throw runtime_error(msg);
	}

	SOCKADDR_IN serverAddress = { 0, };
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port_);
	inet_pton(AF_INET, host_.c_str(), &serverAddress.sin_addr.S_un.S_addr);

	// 교과서에 있는 WSAAsyncSelect
	WSAAsyncSelect(Socket_, g_hwnd, WM_ASYNC, FD_READ);

	if (connect(Socket_, (LPSOCKADDR)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
	{
		string msg = "connect failed. (error code : " + to_string(WSAGetLastError()) + ")";
		cout << msg << endl;
		throw runtime_error(msg);
	}
	else
	{
#ifdef _DEBUG
		cout << "Connected........" << endl;
#endif // _DEBUG
	}
	isConnected_ = true;
}

void Gomoku::Client::Disconnect()
{
	closesocket(Socket_);
	WSACleanup();
	Stop();
#ifdef _DEBUG
	cout << "Disconnected........" << endl;
#endif // _DEBUG
	isConnected_ = false;
}

void Gomoku::Client::Run(LPARAM lParam)
{
	isRunning_ = true;

	switch (lParam)
	{
		case FD_READ:
		{
			GoCenter::GetInstance()->SetPacket(ReceiveStruct());

		}	break;
		default:
			break;
	}
}

bool Gomoku::Client::SendStruct(PACKET packet)
{
	SleepEx(100, true);
	int msgLen = 512;
	char message[512];
	memcpy_s(message, packet.buffer.len, &packet.buffer.buf, packet.buffer.len);
	message[packet.buffer.len] = '\0';
	if (send(Socket_, message, sizeof(packet), 0) < 0)
	{
		perror("Send failed : ");
		return false;
	}
#ifdef _DEBUG
	cout << "데이터 전송 완료" << endl;
#endif // _DEBUG

	return true;
}

PACKET Gomoku::Client::ReceiveStruct()
{
	SleepEx(100, true);
	int msgLen;
	char message[512];
	msgLen = recv(Socket_, message, sizeof(message) - 1, 0);
#ifdef _DEBUG
	if (msgLen == 0)
		return PACKET();
	if (msgLen == -1)
	{
		cout << "인터넷 메시지 받는데 문제가 있습니다" << endl;
		return PACKET();
	}
#endif // _DEBUG
	message[msgLen] = '\0';
	packet_.buffer.buf = message;

#ifdef _DEBUG
	cout << "데이터 수신 완료" << endl;
#endif // _DEBUG

	return packet_;
}

void Gomoku::Client::Stop()
{
	isRunning_ = false;
}

void Gomoku::Client::SetPacket(PACKET pac)
{
	packet_= PACKET(pac);
}
