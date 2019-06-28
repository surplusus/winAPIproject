#pragma once
#include "stdafx.h"
#include <cmath>
#include <vector>
#include <ctime>
using std::vector;
const double PI = atan2(1, 1) * 4;

struct PolarPos {
	int posLTX, posLTY;
	int posRBX, posRBY;

	PolarPos() {}
	PolarPos(int x1, int y1, int x2, int y2) :
		posLTX(x1), posLTY(y1), posRBX(x2), posRBY(y2) {}
	PolarPos(const PolarPos & p) :
		posLTX(p.posLTX), posLTY(p.posLTY), posRBX(p.posRBX), posRBY(p.posRBY) {}
};
class Circle
{
public:
	int x, y;
	int r;
	PolarPos xy;
private:
	int speedX, speedY;
	bool moveXflag;
	bool moveYflag;
	
public:
	Circle(int _x, int _y) : x(_x), y(_y)
	{
		srand((unsigned int)time(NULL));
		r = rand() % 3;
		if (r == 0)
			r = 20;
		else if (r == 1)
			r = 35;
		else if (r == 2)
			r = 50;
		speedX = rand() % 30;
		speedY = rand() % 30;
		moveXflag = rand() % 2;
		moveYflag = rand() % 2;
		xy.posLTX = x - r;
		xy.posLTY = y - r;
		xy.posRBX = x + r;
		xy.posRBY = y + r;
	}
	Circle(const Circle & c) :
		xy(c.xy), x(c.x), y(c.y), r(c.r),
		speedX(c.speedX), speedY(c.speedY), 
		moveXflag(c.moveXflag),moveYflag(c.moveYflag){}
	void Update(HWND & hwnd, vector<Circle> & c);
	void ToggleX() { speedX = -speedX; }
	void ToggleY() { speedY = -speedY; }
private:
	void InputRandomValue();
	void Setxy(int _x, int _y);
	void CheckCollisionAgstWall(HWND & hwnd);
};


void Circle::Update(HWND & hwnd, vector<Circle> & c)
{
	// 충돌판정(토글)
	CheckCollisionAgstWall(hwnd);
	// 위치 변환
	x += speedX;
	y += speedY;
	Setxy(x,y);
	// 원 생명
}
inline void Circle::Setxy(int _x, int _y)
{
	xy.posLTX = _x - r;
	xy.posLTY = _y - r;
	xy.posRBX = _x + r;
	xy.posRBY = _y + r;
}
inline void Circle::CheckCollisionAgstWall(HWND &hwnd)
{
	// 창 안에서 튕기기
	RECT rect;
	GetClientRect(hwnd, &rect);
	if (xy.posLTX <= rect.left)
		ToggleX();
	if (xy.posLTY <= rect.top)
		ToggleY();
	if (xy.posRBX >= rect.right)
		ToggleX();
	if (xy.posRBY >= rect.bottom)
		ToggleY();
}
inline void Circle::InputRandomValue()
{
	srand((unsigned int)time(NULL));
	r = rand() % 3;
	if (r == 0)
		r = 20;
	else if (r == 1)
		r = 35;
	else if (r == 2)
		r = 50;
	speedX = rand() % 50;
	speedY = rand() % 50;
	moveXflag = rand() % 2;
	moveYflag = rand() % 2;
	xy.posLTX = x - r;
	xy.posLTY = y - r;
	xy.posRBX = x + r;
	xy.posRBY = y + r;
}