#pragma once
#include <vector>
#include "Basic_Value.h"
#include "GameObj.h"

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

class StoneMgr : public GameObj
{
private:
	POINT pos_;
	int color_;
public:
	StoneMgr();
	virtual ~StoneMgr() = default;
public:
	void PutStone();
	virtual void Draw(HDC &hdc);
	virtual void Update();
};