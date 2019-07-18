#pragma once
#include "Basic_Value.h"

class RuleMgr
{
private:
	int cntPut_ = 0;
	int turn_ = NONE;
	int TurnBlackOn();
	int TurnWhiteOn();
public:
	RuleMgr();
	~RuleMgr();
public:
	int(RuleMgr::*Func)(void);
	
	int GetCountPut() { return cntPut_; }
};

