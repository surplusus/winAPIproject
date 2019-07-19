#pragma once
class Board : public GameObj
{
public:
	Board();
	virtual ~Board();
public:
	virtual void Draw(HDC &hdc);
	virtual void Update() {}
};

