#include "stdafx.h"
#include "Stone.h"

STONE* GameObj::last_stn = nullptr;
std::vector<std::vector<STONE>> GameObj::stone_pool;

StoneMgr::StoneMgr()
{
}

void StoneMgr::TurnOnYou()
{
	isOnTurn = true;
}

void StoneMgr::PutStone()
{
	stone_pool[coordBrd_.y][coordBrd_.x].color = color_;
	stone_pool[coordBrd_.y][coordBrd_.x].check = true;
	last_stn = &stone_pool[coordBrd_.y][coordBrd_.x];
	if (find(B_stn.begin(), B_stn.end(), last_stn) == B_stn.end() ||
		find(W_stn.begin(), W_stn.end(), last_stn) == W_stn.end())
	{
		if (last_stn->color == BLACK)
			B_stn.push_back(last_stn);
		if (last_stn->color == WHITE)
			W_stn.push_back(last_stn);
	}
}

bool StoneMgr::SetStonePos()
{
	POINT p = GoCenter::GetInstance()->GetInputPos();
	if (0 < p.x && 0 < p.y && p.x < 580 && p.y < 580)
	{
		// 놓여있는 돌과 마우스 점 충돌확인
		for (auto W : W_stn)
		{
			RECT *re = &(W->rect_);
			if (PtInRect(re, p))
				return false;
		}
		for (auto B : B_stn)
		{
			RECT *re = &(B->rect_);
			if (PtInRect(re, p))
				return false;
		}

#ifdef _DEBUG
		if (color_ == BLACK)
			color_ = WHITE;
		else
			color_ = BLACK;
		std::cout << color_ << std::endl;
#endif // _DEBUG
		pos_.x = p.x;
		pos_.y = p.y;
		coordBrd_.x = pos_.x - BoardStartX + (BasicPxl / 2);
		coordBrd_.y = pos_.y - BoardStartY + (BasicPxl / 2);
		coordBrd_.x /= BasicPxl;
		coordBrd_.y /= BasicPxl;

	}
	else
		return false;
	return true;
}

STONE * StoneMgr::LastBlackStone()
{
	if (B_stn.size() != 0)
		return B_stn.back();
	else
		return nullptr;
}

STONE * StoneMgr::LastWhiteStone()
{
	if (W_stn.size() != 0)
		return W_stn.back();
	else
		return nullptr;
}

void StoneMgr::Init()
{
	// make stone pool
	stone_pool.resize(19);
	for (size_t i = 0; i < 19; i++)
	{
		stone_pool[i].clear();
		for (size_t j = 0; j < 19; j++)
		{
			stone_pool[i].push_back(STONE(j, i, NONE, false));
		}
	}
	Subject::Notify(TYPE_EVENT::T_INIT);
}

void StoneMgr::Draw(HDC &hdc)
{
	auto it = W_stn.begin();
	HBRUSH Wbrush = CreateSolidBrush(RGB(235, 235, 235));
	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, Wbrush);
	while (it != W_stn.end())
	{
		Ellipse(hdc, (*it)->cx - CirSize, (*it)->cy - CirSize,
			(*it)->cx + CirSize, (*it)->cy + CirSize);
		it++;
	}
	HBRUSH Bbrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, Bbrush);
	it = B_stn.begin();
	while (it != B_stn.end())
	{
		Ellipse(hdc, (*it)->cx - CirSize, (*it)->cy - CirSize,
			(*it)->cx + CirSize, (*it)->cy + CirSize);
		it++;
	}
	SelectObject(hdc, oldbrush);
	DeleteObject(Wbrush);
	DeleteObject(Bbrush);
	Subject::Notify(TYPE_EVENT::T_RENDER);
}

void StoneMgr::Update()
{
	if (isOnTurn)
	{

		if (SetStonePos()) // 돌을 놓을수 있는곳인가 확인
		{
			PutStone();
			Subject::Notify(TYPE_EVENT::T_PUTSTONE);
		}
		isOnTurn = false;
	}
	
}
