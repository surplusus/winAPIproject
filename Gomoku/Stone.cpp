#include "stdafx.h"
#include "Stone.h"

std::vector<STONE> GameObj::B_stn;
std::vector<STONE> GameObj::W_stn;

StoneMgr::StoneMgr()
{
	GameObj::W_stn.resize(0);
	GameObj::B_stn.resize(0);
}

void StoneMgr::PutStone()
{
	// 룰 에게서 색 가져오기
// test
	if (color_ == BLACK)
		color_ = WHITE;
	else
		color_ = BLACK;
	//
	STONE stn(coordBrd_.x, coordBrd_.y, color_, true);
	if (stn.color == BLACK)
		B_stn.push_back(stn);
	if (stn.color == WHITE)
		W_stn.push_back(stn);
}

bool StoneMgr::TurnOnYou()
{
	isOnTurn = !isOnTurn;
	return isOnTurn;
}

void StoneMgr::SetStonePos()
{
	POINT p = GoCenter::GetInstance()->GetInputPos();
	if (0 < p.x && 0 < p.y && p.x < 580 && p.y < 580)
	{
		pos_.x = p.x;
		pos_.y = p.y;
		coordBrd_.x = pos_.x - BoardStartX + (BasicPxl / 2);
		coordBrd_.y = pos_.y - BoardStartY + (BasicPxl / 2);
		coordBrd_.x /= BasicPxl;
		coordBrd_.y /= BasicPxl;
		onNewPos = true;
	}
}

void StoneMgr::Init()
{
	W_stn.resize(0);
	B_stn.resize(0);
	Subject::Notify(TYPE_EVENT::T_INIT);
}

void StoneMgr::Draw(HDC &hdc)
{
	auto it = W_stn.begin();
	HBRUSH Wbrush = CreateSolidBrush(RGB(235, 235, 235));
	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, Wbrush);
	while (it != W_stn.end())
	{
		Ellipse(hdc, (*it).cx - CirSize, (*it).cy - CirSize,
			(*it).cx + CirSize, (*it).cy + CirSize);
		it++;
	}
	HBRUSH Bbrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, Bbrush);
	it = B_stn.begin();
	while (it != B_stn.end())
	{
		Ellipse(hdc, (*it).cx - CirSize, (*it).cy - CirSize,
			(*it).cx + CirSize, (*it).cy + CirSize);
		it++;
	}
	SelectObject(hdc, oldbrush);
	DeleteObject(Wbrush);
	DeleteObject(Bbrush);
}

void StoneMgr::Update()
{
	SetStonePos();
	
	if (onNewPos)
	{
		Subject::Notify(TYPE_EVENT::T_PUTSTONE);
		if (isOnTurn) {
			PutStone();
			isOnTurn = false;
		}
		onNewPos = false;
	}
}
