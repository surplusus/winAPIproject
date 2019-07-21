#include "SilverServer.h"
#include "Board.h"
#include <iostream>
#include <string>
#include <thread>
#include <stdexcept>
using namespace std;
using namespace Gomoku;

int main()
{
	SilverServer silverServer("127.0.0.1", 8000, 5);

	try {
		silverServer.StartUp();
		silverServer.Run();
	}
	catch (const runtime_error& error) {
		cout << error.what() << endl;
		return 0;
	}

	char key;
	while (cin.get(key))
	{
		if (key == 'q' || key == 'Q')
			break;
	}

	silverServer.Stop();
	
	silverServer.ShutDown();
	return 0;
}