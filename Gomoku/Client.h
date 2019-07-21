#pragma once
#include "Basic_Value.h"
namespace Gomoku
{
	class Client
	{
	private:
		std::string host_;
		int port_;
		SOCKET Socket_;
		PACKET packet_;
		bool isRunning_ = false;
		bool isConnected_ = false;
	public:
		Client(const std::string& host, int port);
	public:
		void Connect();
		void Disconnect();
		void Run(LPARAM lParam);
		bool SendStruct(PACKET packet);
		PACKET ReceiveStruct();
		void Stop();
		PACKET& GetPacket() { return packet_; }
		void SetPacket(PACKET pac);
		bool CheckRunning() { return isRunning_; }
		bool CheckConnected() { return isConnected_; }
	};
}
