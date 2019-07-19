#pragma once
namespace Gomoku
{
	class Client
	{
	private:
		std::string host_;
		int port_;
		SOCKET serverSocket_;
		bool isRunning_;
	public:
		Client(const std::string& host, int port);
	public:
		void Connect();
		void Disconnect();
		void Run();
		void Stop();
	};
}
