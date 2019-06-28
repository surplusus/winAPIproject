#pragma once
#include "Vector2.h"
#include <list>
#include <map>
#include <Windows.h>

class StateInterface;

enum {
	Vertical = 1, Horizontal = 2, Diagonal = 3
};

class Ball {
public:
	Vector2 pos;
	Vector2 dir;
	int radius = 20;
public:
	Ball(int x, int y) : pos(x, y), dir(0, 0) {}
	bool CheckCollision();
	void Move();
};

class BallManager
{
protected:
	static BallManager* instance;
	BallManager();
	BallManager(const BallManager & other) {}
	~BallManager();
public:
	static BallManager* GetInstance() {
		if (nullptr == instance)
			instance = new BallManager();
		return instance;
	}
	static void ReleaseInstance() {
		if (nullptr != instance)
			delete instance;
	}
public:
	std::list<Ball*> balls;
	std::map<int, StateInterface*> states;
	StateInterface* activeState;
public:
	void ShiftState(WPARAM wParam);
	void Create(int x, int y);
};

BallManager* BallManager::instance = nullptr;