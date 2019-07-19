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
	rule_->ChangeTurn();
	// int c = BLACK or WHITE;
	SetInputPos(pt);
	stones_->PutStone(inputPos_, BLACK);
}

void GoCenter::Render(HDC &hdc)
{
	board_->Draw(hdc);
	stones_->Draw(hdc);
}

void GoCenter::Release()
{
	delete rule_;
	delete board_;
	delete stones_;
}

void GoCenter::SetInputPos(POINT pt)
{

	inputPos_.x = pt.x;
	inputPos_.y = pt.y;
}
