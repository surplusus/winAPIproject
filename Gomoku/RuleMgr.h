#pragma once
#include "Basic_Value.h"
class GameObj;

class RuleMgr : public GameObj
{
private:
	int cntPut_ = 0;
	int turn_ = NONE;
	int myStn_ = BLACK;
	POINT curPos_;
	bool isEnd = false;

	STONE* last_black_stn;
	STONE* last_white_stn;

	int TurnBlackOn();
	int TurnWhiteOn();
public:
	RuleMgr();
	virtual ~RuleMgr() {}
public:
	int ChangeTurn();
	int GetCountPut() { return cntPut_; }
	bool Judge(const POINT pos);
	bool Check5Stones();
	void Win();
	void Lose();
	void SetLastBlackStone(STONE* st);
	void SetLastWhiteStone(STONE* st);
	
	virtual void Init();
	virtual void Draw(HDC &hdc);
	virtual void Update();
};

