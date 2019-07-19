#pragma once
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

namespace Gomoku
{
	class SilverServer
	{
	public:
		SilverServer(const std::string& host, int port, int backlog);
	public:
		void StartUp();
		void ShutDown();
		void Run();
		void Stop();
	private:
		std::string host_;
		int port_;
		int backlog_;
		SOCKET socket_;
		bool isRunning_;
	};
}

