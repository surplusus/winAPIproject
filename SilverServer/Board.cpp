#include "Board.h"
#include "Packet.h"
#include <WinSock2.h>
namespace Gomoku
{
	Board::Board()
	{
		stone_pool.resize(19);
		for (size_t i = 0; i < 19; i++)
		{
			for (size_t j = 0; j < 19; j++)
			{
				stone_pool[i].push_back(TYPE_COLOR::NONE);
			}
		}
	}

	void Board::NoteBoard(ST_STONE st)
	{
		stone_pool[st.y][st.x] = static_cast<TYPE_COLOR>(st.color);
	}

	void Board::ExstractMsgFromChar(char * msg)
	{
		int offset = 0;
		memcpy_s(&stone_, sizeof(ST_STONE), msg, sizeof(ST_STONE));
		offset += sizeof(ST_STONE);
		memcpy_s(&status_, sizeof(ST_STATUS), msg + offset, sizeof(ST_STATUS));
		NoteBoard(stone_);
	}

	inline void Board::ImportMsgToChar(Packet * pack)
	{
		ST_STATUS newStatus;
		ST_STONE newStone;

		if (status_.turn == BLACK)
			newStatus.turn = WHITE;
		else
			newStatus.turn = BLACK;

		if (Check5Stones())
			newStatus.win = stone_.color;
		else
			newStatus.win = 0;

		memcpy_s(&pack->buffer.buf, pack->buffer.len, (CHAR*)&newStatus, sizeof(ST_STATUS));

	}

	bool Board::Check5Stones()
	{
		POINT curPos_;
		curPos_.x = stone_.x;
		curPos_.x = stone_.y;
		// 우하향
		for (int i = -4; i <= 4; i++)
		{
			int x1 = curPos_.x + i;
			int y1 = curPos_.y + i;
			if (x1 < 0 || y1 < 0 || x1 >= 19 || y1 >= 19)
				continue;
			int stnInLine = 0;
			for (int j = 0; j < 5; j++)
			{
				int x2 = x1 + j;
				int y2 = y1 + j;
				if (x2 < 0 || y2 < 0 || x2 >= 19 || y2 >= 19)
					continue;

				if (stone_pool[y2][x2] == stone_.color)
					stnInLine++;
				else
					break;
			}
			if (stnInLine == 5)
				return true;
		}
		// 우상향
		for (int i = -4; i <= 4; i++)
		{
			int x1 = curPos_.x + i;
			int y1 = curPos_.y - i;
			if (x1 < 0 || y1 < 0 || x1 >= 19 || y1 >= 19)
				continue;
			int stnInLine = 0;
			for (int j = 0; j < 5; j++)
			{
				int x2 = x1 + j;
				int y2 = y1 - j;
				if (x2 < 0 || y2 < 0 || x2 >= 19 || y2 >= 19)
					continue;

				if (stone_pool[y2][x2] == stone_.color)
					stnInLine++;
				else
					break;
			}
			if (stnInLine == 5)
				return true;
		}
		// 가로
		for (int i = -4; i <= 4; i++)
		{
			int x1 = curPos_.x + i;
			int y1 = curPos_.y;
			if (x1 < 0 || y1 < 0 || x1 >= 19 || y1 >= 19)
				continue;
			int stnInLine = 0;
			for (int j = 0; j < 5; j++)
			{
				int x2 = x1 + j;
				int y2 = y1;
				if (x2 < 0 || y2 < 0 || x2 >= 19 || y2 >= 19)
					continue;

				if (stone_pool[y2][x2] == stone_.color)
					stnInLine++;
				else
					break;
			}
			if (stnInLine == 5)
				return true;
		}
		// 세로
		for (int i = -4; i <= 4; i++)
		{
			int x1 = curPos_.x;
			int y1 = curPos_.y + i;
			if (x1 < 0 || y1 < 0 || x1 >= 19 || y1 >= 19)
				continue;
			int stnInLine = 0;
			for (int j = 0; j < 5; j++)
			{
				int x2 = x1;
				int y2 = y1 + j;
				if (x2 < 0 || y2 < 0 || x2 >= 19 || y2 >= 19)
					continue;

				if (stone_pool[y2][x2] == stone_.color)
					stnInLine++;
				else
					break;
			}
			if (stnInLine == 5)
				return true;
		}
		return false;
	}

}
