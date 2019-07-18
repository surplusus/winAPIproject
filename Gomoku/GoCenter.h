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
	static void ReleaseInstance() {
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
	void Release();
public:
	void SetInputPos(POINT pt);
};

