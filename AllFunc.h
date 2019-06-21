#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <ctime>

POINT MakeBig5Point(int cpoX, int cpoY, int r, int order)
{
	double PI = atan2(1, 1) * 4;
	POINT point;
	double pos[2];
	int i = order;
	// 중심점을 기준으로 각도 theta를 구함
	// theta = (배열 /2) * (360도 / 5)
	double theta = i * (2 * PI / 5) - (PI /2);
	//double degtheta = theta * 360 / (2 * PI);
	pos[0] = cos(theta) * r + cpoX;
	pos[1] = sin(theta) * r + cpoY;

	point = { (int)pos[0],(int)pos[1] };
	return point;
}
POINT MakeSmall5Point(int cpoX, int cpoY, int r, int order)
{
	double PI = atan2(1, 1) * 4;
	POINT point;
	double pos[2];
	int i = order;
	// 중심점을 기준으로 각도 theta를 구함
	// theta = (배열 /2) * (360도 / 5)
	double theta = i * (2 * PI / 5) + (PI / 2);
	//double degtheta = theta * 360 / (2 * PI);
	pos[0] = cos(theta) * r + cpoX;
	pos[1] = sin(theta) * r + cpoY;

	point = { (int)pos[0],(int)pos[1] };
	return point;
}
POINT MakeIntersection(POINT p1, POINT p2, POINT k1, POINT k2)
{
	double p1x = p1.x;	double p1y = p1.y;
	double p2x = p2.x;	double p2y = p2.y;
	double k1x = k1.x;	double k1y = k1.y;
	double k2x = k2.x;	double k2y = k2.y;
	//점 p1, p2를 잇는 직선의 방정식 (기울기)
	double a1 = (p2y - p1y) / (p2x - p1x);
	//점 p1, p2를 잇는 직선의 방정식 (y절편) 
	double b1 = p1y - (p2y - p1y) / (p2x - p1x) * p1x;

	//점 k1, 12를 잇는 직선의 방정식
	double a2 = (k2y - k1y) / (k2x - k1x);
	double b2 = k1y - (k2y - k1y) / (k2x - k1x) * k1x;

	POINT result = { -((b2-b1) / (a2-a1)), -(a1 * ((b2-b1)/(a2-a1)) - b1) };

	return result;
}

void MakeStar(HDC hdc, int cpoX, int cpoY, int r)
{
	POINT p[10];
	POINT pbig[5];
	POINT psmall[5];
	//POINT tmp[5];
	int i;
	for (i = 0; i < 5; i++)
		pbig[i] = MakeBig5Point(cpoX, cpoY, r, i);

	/*for (i = 0; i < 5; i++)
		tmp[i] = MakeSmall5Point(cpoX, cpoY, 75, i);*/
	
	for (i = 0; i < 5; ++i)
		psmall[i] = MakeIntersection(pbig[(i+4) % 5], pbig[(i + 1) % 5], pbig[i % 5], pbig[(i + 2) % 5]);

	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
			p[i] = pbig[i / 2];
		else
			p[i] = psmall[i / 2];
	}
	Polygon(hdc, p, 10);
}

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
	int x, y;
	int r;
	PolarPos xy;
	bool moveXflag = true;
	bool moveYflag = true;

	explicit Circle(int _x, int _y, int _r) : x(_x), y(_y), r(_r)
	{
		xy.posLTX = x - r;
		xy.posLTY = y - r;
		xy.posRBX = x + r;
		xy.posRBY = y + r;
	}
	explicit Circle(int _pos1X, int _pos1Y, int _pos2X, int _pos2Y)
		: xy(_pos1X, _pos1Y,_pos2X, _pos2Y)
	{
		x = (_pos1X + _pos2X) / 2;
		y = (_pos1Y + _pos2Y) / 2;
		r = x - _pos1X;
	}
	Circle(const Circle & c) : 
		xy(c.xy), x(c.x), y(c.y), r(c.r) {}
	void ToggleXflag() { moveXflag = !moveXflag; }
	void ToggleYflag() { moveYflag = !moveYflag; }
};

void DrawSunFlower(const HDC & hdc, int x, int y, int r)
{
	Circle big_c2(x, y, r - (2 * 3.14 * r / 24));
	Ellipse(hdc, big_c2.pos1X, big_c2.pos1Y, big_c2.pos2X, big_c2.pos2Y);

	double theta[12]; // = { 30,60,90,120,150,180,210,240,270,300,330,360 };
	int degree = 30;
	int angle = 0;
	std::generate(std::begin(theta), std::end(theta),
		[&degree, &angle] { angle += degree; return angle; });

	for (auto i : theta)
	{
		double rad = i * 3.14 / 180;
		double sx = cos(rad) * r;
		double sy = sin(rad) * r;
		double sr = 2 * 3.14 * r / 24;
		Circle small_c1(x + sx, y + sy, sr);
		Ellipse(hdc, small_c1.pos1X, small_c1.pos1Y, small_c1.pos2X, small_c1.pos2Y);

	}
}

#define BSIZE  40
double LengthPts(int x1, int y1, int x2, int y2)
{
	return (sqrt((float)(x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)));
}
BOOL InCircle(int x, int y, int mx, int my)
{
	if (LengthPts(x, y, mx, my) < BSIZE)
		return TRUE;
	else
		return FALSE;
}