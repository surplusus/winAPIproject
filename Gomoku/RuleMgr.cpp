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

bool RuleMgr::Judge(const POINT stn_pos)
{
	auto W_iter = GameObj::W_stn;
	auto B_iter = GameObj::B_stn;
	for (auto W : GameObj::W_stn)
	{
		RECT *re = &(W.rect_);
		if (PtInRect(re, stn_pos))
			return false;
	}

	for (auto B : GameObj::B_stn)
	{
		RECT *re = &(B.rect_);
		if (PtInRect(re, stn_pos))
			return false;
	}

	return true;
}

void RuleMgr::Init()
{
	Subject::Notify(TYPE_EVENT::T_INIT);
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
