#include "stdafx.h"
#include "GameCenter.h"
#include "State.h"
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
		activeState = states[Vertical];
	case 0x32:	// 숫자2
		activeState = states[Horizontal];
	case 0x33:	// 숫자3
		activeState = states[Diagonal];
	default:
		break;
	}
}