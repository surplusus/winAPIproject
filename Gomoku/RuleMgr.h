#pragma once
#include "Basic_Value.h"

class RuleMgr : public GameObj
{
private:
	int cntPut_ = 0;
	int turn_ = NONE;
	int whosConnect_[2];
	int TurnBlackOn();
	int TurnWhiteOn();
public:
	RuleMgr();
	virtual ~RuleMgr() {}
public:
	int ChangeTurn();
	int GetCountPut() { return cntPut_; }
	virtual void Draw(HDC &hdc) {}
	virtual void Update();
};

