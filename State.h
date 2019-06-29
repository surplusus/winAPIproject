#pragma once

class StateInterface
{
public:
	virtual void Update() = 0;
	virtual void Render(const HDC & hdc) = 0;
};

class HorizontalState : public StateInterface {
	virtual void Update();
	virtual void Render(const HDC & hdc);
};

class VerticalState : public StateInterface {
	virtual void Update();
	virtual void Render(const HDC & hdc);
};

class DiagonalState : public StateInterface {
	virtual void Update();
	virtual void Render(const HDC & hdc);
};