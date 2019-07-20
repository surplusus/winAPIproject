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
public:
	StoneMgr();
	virtual ~StoneMgr() {}
public:
	virtual void Init();
	virtual void Draw(HDC &hdc);
	virtual void Update();
	
	void PutStone();
	bool TurnOnYou();
	void SetStonePos();
	POINT GetCoordinate() { return coordBrd_; }
};