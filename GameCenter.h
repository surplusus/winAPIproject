#pragma once
#include <map>
#include "State.h"

class Ball;
class BallManager;

class GameCenter
{
public:
	GameCenter();
	~GameCenter();
public:
	BallManager* BM;
	std::map<int, StateInterface*> states;
	StateInterface* activeState;
	void ShiftState(WPARAM wParam);
};

