#include "stdafx.h"
#include "GoCenter.h"
#include "RuleMgr.h"
#include "Board.h"
#include "Stone.h"
#include "Basic_Value.h"

GoCenter* GoCenter::Instance = nullptr;

void GoCenter::Init()
{
	rule_ = new RuleMgr;
	board_ = new Board;
	stones_ = new StoneMgr;
}

void GoCenter::Update(const POINT &pt)
{
	// int c = BLACK or WHITE;
	SetInputPos(pt);

	POINT p1 = { 4,4 };
	POINT p2 = { 5,14 };
	stones_->PutStone(p1, BLACK);
	stones_->PutStone(p2, WHITE);
}

void GoCenter::Render(HDC &hdc)
{
	board_->Draw(hdc);
	stones_->Draw(hdc);
}

void GoCenter::SetInputPos(POINT pt)
{
	inputPos_.x = pt.x;
	inputPos_.y = pt.y;
}
