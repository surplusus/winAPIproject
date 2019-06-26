#pragma once
#include <list>

const int GRID = 20;
const int RADIUS = 10;
class CIRCLE {
public:
	int x;
	int y;
	int radius;
	CIRCLE(int _x = 0, int _y = 0, int _radius = RADIUS) 
		: x(_x),y(_y),radius(_radius) {}
	virtual ~CIRCLE() {}
};
class SNAKE {
public:
	enum {
		UP = 1, RIGHT =2, DOWN, LEFT
	};
	CIRCLE head;
	std::list<CIRCLE*> body;
	CIRCLE prey;
	int dir = 2;
	static RECT gameView;
	static RECT UI;
	bool eatFlag = false;
	bool life = true;
	SNAKE();
	~SNAKE();
	void Update(HDC hdc);
	static void GameWindow(HWND & hwnd);
	void DrawSnake(HDC hdc);
	void Move();
	void MakePrey();
	bool CheckEattingPrey();
	bool IsAlive();
};

