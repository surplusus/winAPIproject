#pragma once
#include "Basic_Value.h"
class GameObj;

class RuleMgr : public GameObj
{
private:
	int cntPut_ = 0;
	int turn_ = NONE;
	int whosConnect_[2];
	POINT pos_;

	int TurnBlackOn();
	int TurnWhiteOn();
public:
	RuleMgr();
	virtual ~RuleMgr() {}
public:
	int ChangeTurn();
	int GetCountPut() { return cntPut_; }
	bool Judge(const POINT stn_pos);
	virtual void Init();
	virtual void Draw(HDC &hdc) {}
	virtual void Update() {}
};

