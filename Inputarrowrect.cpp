// winAPIPractice.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
#include "stdafx.h"
#include "winAPIPractice.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: ���⿡ �ڵ带 �Է��մϴ�.

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINAPIPRACTICE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIPRACTICE));
	MSG msg;

	// �⺻ �޽��� �����Դϴ�:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

//  �Լ�: MyRegisterClass()
//  �뵵: â Ŭ������ ����մϴ�.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIPRACTICE));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPIPRACTICE);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassExW(&wcex);
}

//   �Լ�: InitInstance(HINSTANCE, int)
//   �뵵: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//   �ּ�:
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd)
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}
//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//  �뵵: �� â�� �޽����� ó���մϴ�.
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int drawflag;
	static HBRUSH defBrush = CreateSolidBrush(RGB(245, 245, 245));
	static HBRUSH newBrush = CreateSolidBrush(RGB(235, 5, 5));
	static HPEN hPen = CreatePen(PS_DOT, 1, RGB(5, 5, 5));

	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// �޴� ������ ���� �м��մϴ�:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT rect;

		//oldPen = (HPEN)SelectObject(hdc, hPen);	// SelectObject �Լ��� return �� : default
		//oldBrush = (HBRUSH)SelectObject(hdc, hBrush); // SelectObject �Լ��� return �� : default

		//MakeStar(hdc, 300, 300, 100);
		Rectangle(hdc, 200, 200, 300, 300);
		rect = { 200, 200, 300, 300 };
		DrawText(hdc, _T("Left"), 4, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		Rectangle(hdc, 300, 100, 400, 200);
		rect = { 300, 100, 400, 200 };
		DrawText(hdc, _T("TOP"), 3, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		Rectangle(hdc, 400, 200, 500, 300);
		rect = { 400,200,500,300 };
		DrawText(hdc, _T("RIGHT"), 5, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		Rectangle(hdc, 300, 300, 400, 400);
		rect = { 300,300,400,400 };
		DrawText(hdc, _T("BUTTOM"), 6, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		if (drawflag == 1)	//left
		{
			SelectObject(hdc, newBrush);
			Rectangle(hdc, 200, 200, 300, 300);
			//SelectObject(hdc, defBrush);
		}
		else if (drawflag == 2) {	//top
			SelectObject(hdc, newBrush);
			Rectangle(hdc, 300, 100, 400, 200);
			//SelectObject(hdc, defBrush);
		}
		else if (drawflag == 3) {	// right
			SelectObject(hdc, newBrush);
			Rectangle(hdc, 400, 200, 500, 300);
			//SelectObject(hdc, defBrush);
		}
		else if (drawflag == 4) {	// buttom
			SelectObject(hdc, newBrush);
			Rectangle(hdc, 300, 300, 400, 400);
			//SelectObject(hdc, defBrush);
		}
		else {
			SelectObject(hdc, hPen);
			SelectObject(hdc, defBrush);
		}

		DeleteObject(hPen);
		DeleteObject(newBrush);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_CHAR:
	{

	}
	break;
	case WM_KEYDOWN:
	{

		if (wParam == VK_LEFT)
		{
			drawflag = 1;
			InvalidateRgn(hWnd, NULL, TRUE);
		}
		else if (wParam == VK_UP) {
			drawflag = 2;
			InvalidateRgn(hWnd, NULL, TRUE);
		}
		else if (wParam == VK_RIGHT) {
			drawflag = 3;
			InvalidateRgn(hWnd, NULL, TRUE);
		}
		else if (wParam == VK_DOWN) {
			drawflag = 4;
			InvalidateRgn(hWnd, NULL, TRUE);
		}
	}
	break;
	case WM_KEYUP:
	{
		drawflag = 0;
		InvalidateRgn(hWnd, NULL, TRUE);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}