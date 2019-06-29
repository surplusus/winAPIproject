#include "Ball.h"

BallManager::BallManager()
{
}

BallManager::~BallManager()
{
	if (balls.size() != 0)
	{
		for (auto b : balls)
			delete b;
		balls.clear();
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
