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
	auto list_obj = GetGameObjects();
	for (int i = 0; i < 3; ++i)
	{
		list_obj[i]->Init();
	}
}

void GoCenter::Update()
{
	if (isEnd)
		PostMessage(g_hwnd, WM_DESTROY, 0, 0);
	if (!Observer::is_all_initiated)
		return;
	// mouse
	SetInputPos();

	//클라이언트 선택 받으면
	 //if (클라이언트돌선택)
		stones_->TurnOnYou();

	auto list_obj = GetGameObjects();
	for (int i = 0; i < 3; ++i)
	{
		list_obj[i]->Update();
	}
	inputPos_ = { -1,-1 };
}

void GoCenter::Render(HDC& hdc)
{
	auto list_obj = GetGameObjects();
	for (int i = 0; i < 3; ++i)
	{
		list_obj[i]->Draw(hdc);
	}

#ifdef _DEBUG
	TCHAR szBuff[64];
	auto pt = mousePos;
	wsprintf(szBuff, _T("=== 마우스 좌표 :: X : %d / Y : %d ==="), pt.x, pt.y);
	TextOut(hdc, 10, 620, szBuff, _tcslen(szBuff));
#endif // _DEBUG

	if (!Observer::is_all_rendered)
		std::cout << "render is Undone" << std::endl;
}

void GoCenter::Release()
{
	delete rule_;
	delete board_;
	delete stones_;
}

void GoCenter::onNotify(const Subject * entity, TYPE_EVENT event)
{
	// subject가 (내가 가진애들중) 누군지 판별
	enum TYPE_GO
	{
		T_RULE=0, T_BOARD,T_STONE
	};
	TYPE_GO this_type;
	if (entity == (Subject*)rule_)
		this_type = T_RULE;
	if (entity == (Subject*)board_)
		this_type = T_BOARD;
	if (entity == (Subject*)stones_)
		this_type = T_STONE;

	// subject에게 온 알림 판별
	switch (event)
	{
	case TYPE_EVENT::T_INIT:
	{
		static bool IsInited[3] = { false, };
		IsInited[this_type] = true;
		Observer::is_all_initiated = true;
		for (auto O : IsInited)
			if (O == false)
			{
				Observer::is_all_initiated = false;
				break;
			}

	}	break;
	case TYPE_EVENT::T_RENDER:
	{
		static bool IsRendered[3] = { false, };
		IsRendered[this_type] = true;
		Observer::is_all_rendered = true;
		for (auto O : IsRendered)
			if (O == false)
			{
				Observer::is_all_rendered = false;
				break;
			}
	}	break;
	case TYPE_EVENT::T_UPDATE:
	{
		static bool IsUpdated[3] = { false, };
		IsUpdated[this_type] = true;
		Observer::is_all_updated = true;
		for (auto O : IsUpdated)
			if (O == false)
			{
				Observer::is_all_updated = false;
				break;
			}
	}	break;
	case TYPE_EVENT::T_PUTSTONE:
	{
		rule_->SetLastBlackStone(stones_->LastBlackStone());
		rule_->SetLastWhiteStone(stones_->LastWhiteStone());
		if(rule_->Judge(stones_->GetCoordinate()))
			stones_->TurnOnYou();
	}	break;
	case TYPE_EVENT::T_TURNBLACK:
	{
		cout << "검은돌 둘차례" << endl;
	}	break;
	case TYPE_EVENT::T_TURNWHITE:
	{
		cout << "흰돌 둘차례" << endl;
	}	break;
	case TYPE_EVENT::T_BLACKWIN:
	{
		EndSignal(BLACK);
	}	break;
	case TYPE_EVENT::T_WHITEWIN:
	{
		EndSignal(WHITE);
	}	break;
	default:
		break;
	}
}

void GoCenter::SetInputPos()
{
	if (!Observer::is_all_initiated)
		return;
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		GetCursorPos(&inputPos_);
		ScreenToClient(g_hwnd, &inputPos_);
		mousePos.x = inputPos_.x;
		mousePos.y = inputPos_.y;
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

void GoCenter::EndSignal(TYPE_COL win_stn_col)
{
	if (win_stn_col == BLACK)
	{
		isEnd = BLACK;
		PostMessage(g_hwnd, WM_DESTROY, 0, 0);
	}
	if (win_stn_col == WHITE)
	{
		isEnd = WHITE;
		PostMessage(g_hwnd, WM_DESTROY, 0, 0);
	}
}

void GoCenter::EndMessagePopup()
{
	if (isEnd == BLACK)
	{
		MessageBox(g_hwnd, _T("흑이 이겼습니다!!"), _T("흑"), MB_OK);

	}
	if (isEnd == WHITE)
	{
		MessageBox(g_hwnd, _T("백이 이겼습니다!!"), _T("백"), MB_OK);
	}
}

bool GoCenter::HasMessage()
{
	if (packet_.pos.x != -1 &&
		packet_.pos.y != -1)
		return true;
	else
		return false;
}
