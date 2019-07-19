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
	MyBitMap* LoadBmp(LPWSTR pFileName);
	HDC& GetMemDC() { return hMemDC_; }
	const BITMAP GetBitMapImage() { return bitmapImage_; }
};

class Renderer
{
public:
	Renderer() {}
	~Renderer() {}
private:
	GoCenter* GC;
	HDC hdc_;
	MyBitMap* backBuffer;
	MyBitMap* BackGround;
	bool IsAllInited = false;
public:
	void Init();
	void Render();
	bool IsAllInitiated() { return IsAllInited; }
};

