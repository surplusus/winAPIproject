#pragma once
#include "GoCenter.h"

class MyBitMap
{
private:
	HDC hMemDC_;
	HDC hdc_;
	HBITMAP hBitmap_;
	HBITMAP hOldBitmap_;
	BITMAP bitmapImage_;
public:
	MyBitMap() {}
	~MyBitMap();
public:
	MyBitMap* LoadBmp(LPCWSTR pFileName);
	HDC& GetMemDC() { return hMemDC_; }
	const BITMAP GetBitMapImage() { return bitmapImage_; }
};

class Renderer
{
public:
	Renderer() { Init(); }
	~Renderer() {}
private:
	GoCenter* GC;
	HDC hdc_;
	MyBitMap* backBuffer;
	MyBitMap* BackGround;
public:
	void Init();
	void Render();
};

