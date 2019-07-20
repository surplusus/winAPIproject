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
		rect_.left = cx;
		rect_.top = cy;
		rect_.right = cx + BasicPxl;
		rect_.bottom= cy + BasicPxl;
	}
	_Stone(int _x, int _y, int _color, bool _check) : x(_x), y(_y), check(_check), color(_color) {
		cx = BoardStartX + x * BasicPxl;
		cy = BoardStartY + y * BasicPxl;
		rect_.left = cx;
		rect_.top = cy;
		rect_.right = cx + BasicPxl;
		rect_.bottom = cy + BasicPxl;
	}
}STONE;

class GameObj : public Subject
{
public:
	virtual ~GameObj() {}
protected:
	STONE stone_;	//internal temporary variable
	static std::vector<STONE> W_stn;
	static std::vector<STONE> B_stn;
public:
	virtual void Init() = 0;
	virtual void Draw(HDC &hdc) = 0;
	virtual void Update() = 0;
};

