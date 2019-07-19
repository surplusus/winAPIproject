#pragma once
#include <vector>
class RuleMgr;
class Board;
class Stone;
class StoneMgr;
class Renderer;
class GameObj;

class GoCenter
{
private:
	static GoCenter* Instance;
	GoCenter() {}
	GoCenter(GoCenter&) {}
	~GoCenter() {}
public:
	static GoCenter* GetInstance() {
		if (!Instance)
			Instance = new GoCenter;
		return Instance;	}
	static void ReleaseInstance() {
		delete Instance;	}

private:
	RuleMgr* rule_ = nullptr;
	Board* board_ = nullptr;
	StoneMgr* stones_ = nullptr;
	Renderer* render_ = nullptr;
	POINT inputPos_ = { 0,0 };
	bool IsAllInited = false;
public:
	void Init();
	void Update();
	void Release();
public:
	void SetInputPos();
	bool IsAllInitiated() { return IsAllInited; }
	const Board* GetBoard() { return board_; }
	StoneMgr* GetStones() { return stones_; }
	const POINT& GetInputPos() { return inputPos_; }
	std::vector<GameObj*> GetGameObjects();
};

