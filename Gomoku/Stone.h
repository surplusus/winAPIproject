#pragma once
#include <vector>
#include "Basic_Value.h"

typedef struct _Stone
{
	
	int x;
	int y;
	int cx;
	int cy;
	int color = NONE;
	bool check;

	_Stone() {}
	_Stone(int _x, int _y) : x(_y), y(_y) { 
		cx = BoardStartX + x * BasicPxl; 
		cy = BoardStartY + y * BasicPxl;
	}
	_Stone(int _x, int _y, int _color, bool _check) : x(_x), y(_y), check(_check), color(_color) {
		cx = BoardStartX + x * BasicPxl;
		cy = BoardStartY + y * BasicPxl;
	}
}STONE;

class StoneMgr
{
private:
	std::vector<STONE> W_stn;
	std::vector<STONE> B_stn;
public:
	void PutStone(POINT pos, int color);
	void Draw(HDC &hdc);
};