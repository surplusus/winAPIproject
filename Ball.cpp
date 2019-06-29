#include "Ball.h"

BallManager* BallManager::instance = nullptr;

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

void BallManager::Create(float x, float y)
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
	bool toggle = true;

	if (pos.x <= 10 || pos.x >= 440)
		dir.x = -dir.x;
	if (pos.y <= 10 || pos.y >= 440)
		dir.y = -dir.y;

	pos += dir;
}
