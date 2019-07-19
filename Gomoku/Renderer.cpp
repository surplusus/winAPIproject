#include "stdafx.h"
#include "Renderer.h"
#include "GameObj.h"

MyBitMap::~MyBitMap()
{
	SelectObject(hMemDC_, hOldBitmap_);
	DeleteObject(hBitmap_);
	DeleteDC(hMemDC_);
}

MyBitMap * MyBitMap::LoadBmp(LPWSTR pFileName)
{
	hdc_ = GetDC(g_hwnd);
	hMemDC_ = CreateCompatibleDC(hdc_);
	hBitmap_ = (HBITMAP)LoadImage(NULL, pFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	GetObject(hBitmap_, sizeof(BITMAP), &bitmapImage_);
	if (hBitmap_ == NULL)
	{
		MessageBox(g_hwnd, _T("�̹��� �ε� ����"), _T("�̹��� �ε� ����"), MB_OK);
		exit(0);
	}
	hOldBitmap_ = (HBITMAP)SelectObject(hMemDC_, hBitmap_);

	DeleteObject(hBitmap_);
	DeleteObject(hOldBitmap_);
	return nullptr;
}

void Renderer::Init()
{
	hdc_ = GetDC(g_hwnd);
	backBuffer = (new MyBitMap)->LoadBmp((LPWSTR)_T("./img/background.bmp"));
	backBuffer = (new MyBitMap)->LoadBmp((LPWSTR)_T("./img/background.bmp"));
	GC = GoCenter::GetInstance();
	IsAllInited = true;
}

void Renderer::Render()
{
	if (!IsAllInited)
		return;
	BitBlt(hdc_, 0, 0, BoardWidth, BoardHeight, backBuffer->GetMemDC(), 0, 0, SRCCOPY);
	BitBlt(backBuffer->GetMemDC(), 0, 0, BoardWidth, BoardHeight, BackGround->GetMemDC(), 0, 0, SRCCOPY);

	GoCenter* GC = GoCenter::GetInstance();
	// �� �ڸ��� �׸���
	auto list_obj = GC->GetGameObjects();
	for (int i = 0; i < list_obj.size(); ++i)
	{
		list_obj[i]->Draw(hdc_);
	}

	GC->Render(backBuffer->GetMemDC());
	BitBlt(hdc_, 0, 0, BoardWidth, BoardHeight, backBuffer->GetMemDC(), 0, 0, SRCCOPY);
}
