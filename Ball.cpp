#include "stdafx.h"
#include "Ball.h"
#include "State.h"

BallManager::BallManager()
{
	StateInterface* s;
	s = new VerticalState;
	states.insert(std::make_pair(Vertical, s));
	s = new HorizontalState;
	states.insert(std::make_pair(Horizontal, s));
	s = new DiagonalState;
	states.insert(std::make_pair(Diagonal, s));

	activeState = states[Vertical];
}

BallManager::~BallManager()
{
	for (auto b : balls)
		delete b;
	balls.clear();
}

void BallManager::ShiftState(WPARAM wParam)
{
	switch (wParam)
	{
	case 0x31:	// 숫자1
		activeState = states[Vertical];
	case 0x32:	// 숫자2
		activeState = states[Horizontal];
	case 0x33:	// 숫자3
		activeState = states[Diagonal];
	default:
		break;
	}
}

void BallManager::Create(int x, int y)
{
	Ball *b = new Ball(x,y);
	balls.push_back(b);
}

bool Ball::CheckCollision()
{
	BallManager *BM = BallManager::GetInstance();
	
	for (auto b : BM->balls)
	{
		if (Vector2::DistTwoDot(pos, b->pos) <= radius)
			return true;
	}
	return false;
}

void Ball::Move()
{
	pos += dir;

	if (pos.x <= 0 || pos.x >= 500)
		dir.x = -dir.x;
	if (pos.y <= 0 || pos.y >= 500)
		dir.y = -dir.y;
}
