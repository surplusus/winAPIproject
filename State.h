#pragma once
#include <Windows.h>

class StateInterface
{
public:
	virtual void Update() = 0;
	virtual void Render(const HDC & hdc) = 0;
};

class HorizontalState : public StateInterface {
public:
	virtual void Update();
	virtual void Render(const HDC & hdc);
};

class VerticalState : public StateInterface {
public:
	virtual void Update();
	virtual void Render(const HDC & hdc);
};

class DiagonalState : public StateInterface {
public:
	virtual void Update();
	virtual void Render(const HDC & hdc);
};