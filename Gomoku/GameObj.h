#pragma once
#include "Stone.h"
#include <Windows.h>

class GameObj
{
public:
	virtual ~GameObj() {}
protected:
	STONE stone_;	//internal temporary variable
	std::vector<STONE> W_stn;
	std::vector<STONE> B_stn;
public:
	virtual void Draw(HDC &hdc) = 0;
	virtual void Update() = 0;
};
