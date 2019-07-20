#pragma once
#include "Basic_Value.h"
#include <vector>
class RuleMgr;
class Board;
class Stone;
class StoneMgr;
class Renderer;
class GameObj;
class Subject;

class Observer
{
protected:
	bool is_all_initiated = false;
	bool is_all_updated = false;
	bool is_all_rendered= false;
public:
	virtual ~Observer() {}
	virtual void onNotify(const Subject* entity, TYPE_EVENT event) = 0;
};

class GoCenter : public Observer
{
	// singleTon
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
	// mediator
private:
	RuleMgr* rule_ = nullptr;
	Board* board_ = nullptr;
	StoneMgr* stones_ = nullptr;
	Renderer* render_ = nullptr;
private:	// internal temporary variable
	POINT inputPos_ = { 0,0 };
	POINT mousePos = { 0,0 };
	HDC hdc_;
public:
	void Init();
	void Update();
	void Render(HDC& hdc);
	void Release();
	virtual void onNotify(const Subject* entity, TYPE_EVENT event);
public:
	void SetInputPos();
	const POINT& GetInputPos() { return inputPos_; }
	/*const Board* GetBoard() { return board_; }
	StoneMgr* GetStones() { return stones_; }*/
	std::vector<GameObj*> GetGameObjects();
};

