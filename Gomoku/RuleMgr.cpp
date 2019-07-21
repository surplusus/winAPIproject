#include "stdafx.h"
#include "RuleMgr.h"

RuleMgr::RuleMgr()
{
}

int RuleMgr::ChangeTurn()
{
	if (turn_ == NONE)
	{
		turn_ = BLACK;
		return TurnBlackOn();
	}

	int(RuleMgr::*func)(void);

	if (turn_ == BLACK)
		func = &RuleMgr::TurnBlackOn;
	else
		func = &RuleMgr::TurnWhiteOn;

	return (this->*func)();
}

bool RuleMgr::Judge(const POINT curcoord)
{
	curPos_ = curcoord;
#ifdef _DEBUG
	turn_ = BLACK;
#endif // _DEBUG

	if (last_stn == nullptr)
		return false;
	//else
	//	if (last_stn->color == turn_)	// 지금 내턴인지 판별
	//		return false;
	

	if (last_black_stn == nullptr || last_white_stn == nullptr)	// 이전에 1번도 안두었으면 거름
		return false;

	if (Check5Stones())
	{
		// 오목 완성이면 끝
		if (turn_ == myStn_)
			Win();
		else
			Lose();
		return false;
	}
	else	// 오목 완성 못하면 changeturn()
		turn_ = ChangeTurn();

	return true;
}

bool RuleMgr::Check5Stones()
{
	// 우하향
	for (int i = -4; i <= 4; i++)
	{
		int x1 = curPos_.x + i;
		int y1 = curPos_.y + i;
		if (x1 < 0 || y1 < 0 || x1 >= 19 || y1 >= 19)
			continue;
		int stnInLine = 0;
		for (int j = 0; j < 5; j++)
		{
			int x2 = x1 + j;
			int y2 = y1 + j;
			if (x2 < 0 || y2 < 0 || x2 >= 19 || y2 >= 19)
				continue;

			if (stone_pool[y2][x2].color == last_stn->color)
				stnInLine++;
			else
				break;
		}
		if (stnInLine == 5)
			return true;
	}
	// 우상향
	for (int i = -4; i <= 4; i++)
	{
		int x1 = curPos_.x + i;
		int y1 = curPos_.y - i;
		if (x1 < 0 || y1 < 0 || x1 >= 19 || y1 >= 19)
			continue;
		int stnInLine = 0;
		for (int j = 0; j < 5; j++)
		{
			int x2 = x1 + j;
			int y2 = y1 - j;
			if (x2 < 0 || y2 < 0 || x2 >= 19 || y2 >= 19)
				continue;

			if (stone_pool[y2][x2].color == last_stn->color)
				stnInLine++;
			else
				break;
		}
		if (stnInLine == 5)
			return true;
	}
	// 가로
	for (int i = -4; i <= 4; i++)
	{
		int x1 = curPos_.x + i;
		int y1 = curPos_.y;
		if (x1 < 0 || y1 < 0 || x1 >= 19 || y1 >= 19)
			continue;
		int stnInLine = 0;
		for (int j = 0; j < 5; j++)
		{
			int x2 = x1 + j;
			int y2 = y1;
			if (x2 < 0 || y2 < 0 || x2 >= 19 || y2 >= 19)
				continue;

			if (stone_pool[y2][x2].color == last_stn->color)
				stnInLine++;
			else
				break;
		}
		if (stnInLine == 5)
			return true;
	}
	// 세로
	for (int i = -4; i <= 4; i++)
	{
		int x1 = curPos_.x;
		int y1 = curPos_.y + i;
		if (x1 < 0 || y1 < 0 || x1 >= 19 || y1 >= 19)
			continue;
		int stnInLine = 0;
		for (int j = 0; j < 5; j++)
		{
			int x2 = x1;
			int y2 = y1 + j;
			if (x2 < 0 || y2 < 0 || x2 >= 19 || y2 >= 19)
				continue;

			if (stone_pool[y2][x2].color == last_stn->color)
				stnInLine++;
			else
				break;
		}
		if (stnInLine == 5)
			return true;
	}
	return false;
}

void RuleMgr::Win()
{
	isEnd = true;
#ifdef _DEBUG
	cout << "Win" << endl;
#endif // _DEBUG
	if (myStn_ == BLACK)
		Subject::Notify(TYPE_EVENT::T_BLACKWIN);

}

void RuleMgr::Lose()
{
	isEnd = true;
#ifdef _DEBUG
	cout << "Lose" << endl;
#endif // _DEBUG
	MessageBox(g_hwnd, _T("졌습니다ㅜㅜ"), _T("LOSE"), MB_OK);
	cout << "졌습니다" << endl;
}

void RuleMgr::SetLastBlackStone(STONE * st)
{
	if (st != nullptr)
		last_black_stn = st;
	else
		last_black_stn = nullptr;
}

void RuleMgr::SetLastWhiteStone(STONE * st)
{
	if (st != nullptr)
		last_white_stn = st;
	else
		last_white_stn = nullptr;
}

void RuleMgr::Init()
{
	Subject::Notify(TYPE_EVENT::T_INIT);
}

void RuleMgr::Draw(HDC & hdc)
{
	Subject::Notify(TYPE_EVENT::T_RENDER);
}

void RuleMgr::Update()
{
	/*STONE* just_last_stn;
	if (last_stn->color == BLACK)
		just_last_stn = last_white_stn;
	else
		just_last_stn = last_black_stn;*/

	Subject::Notify(TYPE_EVENT::T_UPDATE);
}

int RuleMgr::TurnBlackOn()
{
	if (turn_ != BLACK)
		cntPut_++;
	turn_ = BLACK;
	Subject::Notify(TYPE_EVENT::T_TURNBLACK);
	return BLACK;
}

int RuleMgr::TurnWhiteOn()
{
	if (turn_ != WHITE)
		cntPut_++;
	turn_ = WHITE;
	Subject::Notify(TYPE_EVENT::T_TURNWHITE);
	return WHITE;
}
