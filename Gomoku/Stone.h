#pragma once
#include "Basic_Value.h"
#include "GameObj.h"
class GameObj;

class StoneMgr : public GameObj
{
private:
	bool isOnTurn = false;
	bool onNewPos = false;
	POINT pos_;
	POINT coordBrd_;
	int color_;
	std::vector<STONE*> W_stn;
	std::vector<STONE*> B_stn;
public:
	StoneMgr();
	virtual ~StoneMgr() {}
public:
	virtual void Init();
	virtual void Draw(HDC &hdc);
	virtual void Update();
	
	void TurnOnYou();
	void PutStone();
	bool SetStonePos();
	void SetStoneColor(TYPE_COL c) { color_ = c; }
	POINT GetCoordinate() { return coordBrd_; }
	STONE* LastBlackStone();
	STONE* LastWhiteStone();
};