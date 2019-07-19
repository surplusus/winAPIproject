#include "stdafx.h"
#include "GoCenter.h"
#include "GameObj.h"
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
	render_ = new Renderer;
	IsAllInited = true;
}

void GoCenter::Update()
{
	if (!IsAllInited)
		return;

	SetInputPos();
	auto list_obj = GetGameObjects();
	for (int i = 0; i < list_obj.size(); ++i)
	{
		list_obj[i]->Update();
	}
	rule_->ChangeTurn();
	// int c = BLACK or WHITE;
	
	stones_->PutStone(inputPos_, BLACK);
}

void GoCenter::Release()
{
	delete rule_;
	delete board_;
	delete stones_;
}

void GoCenter::SetInputPos()
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		GetCursorPos(&inputPos_);
		ScreenToClient(g_hwnd, &inputPos_);
	}
	
}

std::vector<GameObj*> GoCenter::GetGameObjects()
{
	std::vector<GameObj*> list;
	list.push_back((GameObj*)board_); 
	list.push_back((GameObj*)stones_); 
	list.push_back((GameObj*)rule_); 
	return list;
}
