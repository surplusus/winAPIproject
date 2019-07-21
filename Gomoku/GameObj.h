#pragma once
#include <Windows.h>
#include <vector>

class Subject
{
public:
	Subject() {}
	virtual ~Subject() {}
private:
	Observer* observer_;
public:
	// 원래는 아래 둘 있어야함
	// void Register(Observer* ob)
	// void UnRegister(Observer* ob)
protected:
	void Notify(TYPE_EVENT event) {
		if (!observer_)
			observer_ = GoCenter::GetInstance();
		observer_->onNotify(this, event);
	}
};

typedef struct _Stone
{
	int x;
	int y;
	int cx;
	int cy;
	RECT rect_;
	int color = NONE;
	bool check;
	_Stone() {}
	_Stone(int _x, int _y) : x(_y), y(_y) {
		cx = BoardStartX + x * BasicPxl;
		cy = BoardStartY + y * BasicPxl;
		rect_.left = cx - (BasicPxl / 2);
		rect_.top = cy - (BasicPxl / 2);
		rect_.right = cx + BasicPxl - (BasicPxl / 2);
		rect_.bottom= cy + BasicPxl - (BasicPxl / 2);
	}
	_Stone(int _x, int _y, int _color, bool _check) : x(_x), y(_y), check(_check), color(_color) {
		cx = BoardStartX + x * BasicPxl;
		cy = BoardStartY + y * BasicPxl;
		rect_.left = cx - (BasicPxl / 2);
		rect_.top = cy - (BasicPxl / 2);
		rect_.right = cx + BasicPxl - (BasicPxl / 2);
		rect_.bottom = cy + BasicPxl - (BasicPxl / 2);
	}
}STONE;

class GameObj : public Subject
{
public:
	virtual ~GameObj() {}
protected:
	static STONE* last_stn;	//internal temporary variable
	static std::vector<std::vector<STONE>> stone_pool;
public:
	virtual void Init() = 0;
	virtual void Draw(HDC &hdc) = 0;
	virtual void Update() = 0;
};

