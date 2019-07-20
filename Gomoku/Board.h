#pragma once
class GameObj;

class Board : public GameObj
{
public:
	Board();
	virtual ~Board();
public:
	virtual void Init();
	virtual void Draw(HDC &hdc);
	virtual void Update() {}
};

