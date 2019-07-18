#pragma once
class RuleMgr;
class Board;
class Stone;
class StoneMgr;

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
	static void Release() {
		delete Instance;	}

private:
	RuleMgr* rule_ = nullptr;
	Board* board_ = nullptr;
	StoneMgr* stones_ = nullptr;
	POINT inputPos_ = { 0,0 };
public:
	void Init();
	void Update(const POINT &pt);
	void Render(HDC &hdc);
public:
	void SetInputPos(POINT pt);
};

