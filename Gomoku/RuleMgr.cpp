#include "stdafx.h"
#include "RuleMgr.h"


RuleMgr::RuleMgr()
{
}

int RuleMgr::ChangeTurn()
{
	if (turn_ == NONE)
		return TurnBlackOn();

	int(RuleMgr::*func)(void);

	if (whosConnect_[1])
		func = &RuleMgr::TurnBlackOn;
	else
		func = &RuleMgr::TurnWhiteOn;

	return (this->*func)();
}

int RuleMgr::TurnBlackOn()
{
	if (turn_ != BLACK)
		cntPut_++;
	turn_ = BLACK;
	return BLACK;
}

int RuleMgr::TurnWhiteOn()
{
	if (turn_ != WHITE)
		cntPut_++;
	turn_ = WHITE;
	return WHITE;
}
