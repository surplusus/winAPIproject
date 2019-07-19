#include "stdafx.h"
#include "Stone.h"
#include "GoCenter.h"

StoneMgr::StoneMgr()
{
	W_stn.resize(0);
	B_stn.resize(0);
}

void StoneMgr::PutStone()
{
	pos_.x += BasicPxl / 2;
	pos_.y += BasicPxl / 2;
	int x = (pos_.x - BoardStartX) / BasicPxl;
	int y = (pos_.y - BoardStartY) / BasicPxl;

	STONE stn(x, y, color_, true);
	if (stn.color == BLACK)
		B_stn.push_back(stn);
	if (stn.color == WHITE)
		W_stn.push_back(stn);
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
	pos_ = GoCenter::GetInstance()->GetInputPos();
	// 룰 에게서 색 가져오기
	PutStone()
}
