#include "stdafx.h"
#include "SNAKE.h"
#include <ctime>

RECT SNAKE::gameView = { 0, };
RECT SNAKE::UI = { 0, };

SNAKE::SNAKE()
{
	head.x = 200; head.y = 200;
	CIRCLE* b1 = new CIRCLE(200,200,RADIUS);
	body.push_back(b1);
	MakePrey();
}

SNAKE::~SNAKE()
{
	CIRCLE *tmp = &head;
	delete tmp;
	for (auto & it : body)
		delete it;
}

void SNAKE::Update(HDC hdc)
{
	CIRCLE* nb;
	if (life)
		nb = new CIRCLE(head);
	else
		return;
	Move();
	life = IsAlive();

	eatFlag = CheckEattingPrey();
	body.push_front(nb);
	if (eatFlag == true)
	{
		eatFlag = false;
		MakePrey();
		return;
	}
	else
	{
		body.pop_back();
	}
}

void SNAKE::GameWindow(HWND & hwnd)
{
	GetClientRect(hwnd, &gameView);
	gameView.bottom = 590;
	gameView.left += 50;
	gameView.top += 50;
	gameView.right = 590;
	GetClientRect(hwnd, &UI);
	UI.bottom = 590;
	UI.left = 600;
	UI.top += 50;
	UI.right = 800;
}

void SNAKE::DrawSnake(HDC hdc)
{
	Ellipse(hdc, head.x-RADIUS,head.y-RADIUS,head.x+RADIUS,head.y+RADIUS);
	Ellipse(hdc, prey.x-RADIUS,prey.y-RADIUS,prey.x+RADIUS,prey.y+RADIUS);
	for (auto it : body)
	{
		Ellipse(hdc, it->x - RADIUS, it->y - RADIUS, it->x + RADIUS, it->y + RADIUS);
	}
}

void SNAKE::Move()
{
	switch (dir)
	{
	case UP:
		head.y -= GRID;
		break;
	case RIGHT:
		head.x += GRID;
		break;
	case DOWN:
		head.y += GRID;
		break;
	case LEFT:
		head.x -= GRID;
		break;
	}
}

void SNAKE::MakePrey()
{
	srand((unsigned int)time(NULL));
	prey.x = rand() % 27 * 20+60;
	srand((unsigned int)time(NULL));
	prey.y = rand() % 27 * 20+60;
	prey.radius = RADIUS;
}

bool SNAKE::CheckEattingPrey()
{
	if (prey.x - 5 <= head.x && head.x <= prey.x + 5
		&& prey.y - 5 <= head.y && head.y <= prey.y + 5)
		return true;
	else
		return false;
}

bool SNAKE::IsAlive()
{
	if (gameView.top > head.y || gameView.right < head.x
		|| gameView.bottom < head.y || gameView.left > head.x)
		return false;
	for (auto it : body)
		if (it->x == head.x && it->y == head.y)
			return false;
	return true;
}
