#pragma once
#include "Basic_Value.h"

class RuleMgr
{
private:
	int cntPut_ = 0;
	int turn_ = NONE;
	int whosConnect_[2];
	int TurnBlackOn();
	int TurnWhiteOn();
public:
	RuleMgr();
	~RuleMgr() {}
public:
	int ChangeTurn();
	int GetCountPut() { return cntPut_; }
};

