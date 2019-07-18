#include "stdafx.h"
#include "Board.h"
#include "Basic_Value.h"

Board::Board()
{
}

Board::~Board()
{
}

void Board::Draw(HDC & hdc)
{
	for (int i = 0; i < 19; ++i)
	{
		MoveToEx(hdc, BoardStartX + i * BasicPxl, BoardStartY, NULL);
		LineTo(hdc, BoardStartX + i * BasicPxl, BoardStartY + BasicPxl*18);
	}
	for (int i = 0; i < 19; ++i)
	{
		MoveToEx(hdc, BoardStartX, BoardStartY + i * BasicPxl, NULL);
		LineTo(hdc, BoardStartX + BasicPxl * 18, BoardStartY + i * BasicPxl);
	}
	HBRUSH hbrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

	int r1[3] = { 117,297,477 };
	int r2[3] = { 123,303,483 };
	for(int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			Ellipse(hdc, r1[j], r1[i], r2[j], r2[i]);
		}
	}
	
	SelectObject(hdc, oldbrush);
	DeleteObject(hbrush);
}
