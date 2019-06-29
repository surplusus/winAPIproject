#include "GameCenter.h"
#include "Ball.h"

GameCenter::GameCenter()
{
	StateInterface* s;
	s = new VerticalState;
	states.insert(std::make_pair(Vertical, s));
	s = new HorizontalState;
	states.insert(std::make_pair(Horizontal, s));
	s = new DiagonalState;
	states.insert(std::make_pair(Diagonal, s));

	activeState = states[Vertical];
	BM = BallManager::GetInstance();
}

GameCenter::~GameCenter()
{
	for (auto st : states)
		delete st.second;
	states.clear();
}

void GameCenter::ShiftState(WPARAM wParam)
{
	switch (wParam)
	{
	case 0x31:	// 숫자1
	{
		activeState = states[Vertical];
		for (auto b : BM->balls)
		{
			b->dir.x = 0;	b->dir.y = 10;
		}
	}	break;
	case 0x32:	// 숫자2
	{
		activeState = states[Horizontal];
		for (auto b : BM->balls)
		{
			b->dir.x = 10;	b->dir.y = 0;
		}
	}break;
	case 0x33:	// 숫자3
	{
		activeState = states[Diagonal];
		for (auto b : BM->balls)
		{
			b->dir.x = 10;	b->dir.y = 10;
		}
	}
	default:
		break;
	}
}