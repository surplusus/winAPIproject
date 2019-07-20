#include "stdafx.h"
#include "Renderer.h"
#include "GameObj.h"

MyBitMap::~MyBitMap()
{
	SelectObject(hMemDC_, hOldBitmap_);
	DeleteObject(hBitmap_);
	DeleteDC(hMemDC_);
}

MyBitMap * MyBitMap::LoadBmp(LPCWSTR pFileName)
{
	hdc_ = GetDC(g_hwnd);
	hMemDC_ = CreateCompatibleDC(hdc_);
	hBitmap_ = (HBITMAP)LoadImage(NULL, pFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	GetObject(hBitmap_, sizeof(BITMAP), &bitmapImage_);
	if (!hBitmap_)
	{
		MessageBox(g_hwnd, _T("이미지 로드 실패"), _T("이미지 로드 실패"), MB_OK);
		exit(0);
	}
	hOldBitmap_ = (HBITMAP)SelectObject(hMemDC_, hBitmap_);

	DeleteObject(hBitmap_);
	DeleteObject(hOldBitmap_);
	return this;
}

void Renderer::Init()
{
	hdc_ = GetDC(g_hwnd);
	backBuffer = (new MyBitMap)->LoadBmp((LPCWSTR)_T("img/background.bmp"));
	BackGround = (new MyBitMap)->LoadBmp((LPCWSTR)_T("img/background.bmp"));
	GC = GoCenter::GetInstance();
}

void Renderer::Render()
{
	BitBlt(hdc_, 0, 0, BoardWidth, BoardHeight, backBuffer->GetMemDC(), 0, 0, SRCCOPY);
	BitBlt(backBuffer->GetMemDC(), 0, 0, BoardWidth, BoardHeight, BackGround->GetMemDC(), 0, 0, SRCCOPY);

	GoCenter* GC = GoCenter::GetInstance();
	// 이 자리에 그리기
	//GC->Render(hdc_);
	GC->Render(backBuffer->GetMemDC());

	BitBlt(hdc_, 0, 0, BoardWidth, BoardHeight, backBuffer->GetMemDC(), 0, 0, SRCCOPY);
}
