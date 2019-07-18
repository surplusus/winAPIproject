#include "stdafx.h"
#include "Stone.h"

void StoneMgr::PutStone(POINT pos, int color)
{
	int x = (pos.x - BoardStartX) / BasicPxl;
	int y = (pos.y - BoardStartY) / BasicPxl;

	STONE stn(x, y, color, true);
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
	}
	HBRUSH Bbrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, Bbrush);
	it = B_stn.begin();
	while (it != B_stn.end())
	{
		Ellipse(hdc, (*it).cx - CirSize, (*it).cy - CirSize,
			(*it).cx + CirSize, (*it).cy + CirSize);
	}
	SelectObject(hdc, oldbrush);
	DeleteObject(Wbrush);
	DeleteObject(Bbrush);
}
