#include "stdafx.h"
#include "Client.h"
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::runtime_error;

Gomoku::Client::Client(const std::string & host, int port) : 
	host_(host), port_(port), serverSocket_(-1), isRunning_(true)
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

	serverSocket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket_ == INVALID_SOCKET)
	{
		string msg = "socket failed. (error code : " + to_string(WSAGetLastError()) + ")";
		cout << msg << endl;
		throw runtime_error(msg);
	}

	SOCKADDR_IN serverAddress = { 0, };
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port_);
	inet_pton(AF_INET, host_.c_str(), &serverAddress.sin_addr.S_un.S_addr);

	if (connect(serverSocket_, (LPSOCKADDR)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
	{
		string msg = "connect failed. (error code : " + to_string(WSAGetLastError()) + ")";
		cout << msg << endl;
		throw runtime_error(msg);
	}
	else
	{
		cout << "Connected........" << endl;
	}
}

void Gomoku::Client::Disconnect()
{
	closesocket(serverSocket_);
	WSACleanup();
}

void Gomoku::Client::Run()
{
	while (isRunning_)
	{

	}
}

void Gomoku::Client::Stop()
{
	isRunning_ = false;
}
