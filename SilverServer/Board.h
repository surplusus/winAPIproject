#pragma once
#include <vector>
#include <Windows.h>
using std::vector;
class Packet;
namespace Gomoku
{
	typedef struct _tagStone
	{
		int x = -1;		//coordinate X
		int y = -1;		//coordinate Y
		int color = 0;	//stone color	1: Black 2:White
	} ST_STONE;

	typedef struct _tagStatus
	{
		int turn = 0;	//turn		1:Black 2:White
		int win = 0;	//win flag	1:BlackWin 2:WhiteWin
	} ST_STATUS;

	enum TYPE_COLOR
	{
		NONE = 0, BLACK = 1, WHITE = 2
	};

	class Board
	{
	private:
		ST_STONE stone_;
		ST_STATUS status_;
		vector<vector<TYPE_COLOR>> stone_pool;
	public:
		Board();
		~Board() = default;

		void NoteBoard(ST_STONE st);
		void ExstractMsgFromChar(char* msg);
		void ImportMsgToChar(Packet* pack);
		bool Check5Stones();
	};
}

