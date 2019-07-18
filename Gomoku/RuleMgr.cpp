#include "stdafx.h"
#include "RuleMgr.h"


RuleMgr::RuleMgr()
{
	Func = &RuleMgr::TurnBlackOn;
}

int RuleMgr::TurnBlackOn()
{
	if (turn_ == WHITE)
		cntPut_++;
	turn_ = BLACK;
	return BLACK;
}

int RuleMgr::TurnWhiteOn()
{
	if (turn_ == WHITE)
		cntPut_++;
	turn_ = WHITE;
	return WHITE;
}
