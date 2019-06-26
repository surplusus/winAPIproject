// winAPIPractice.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
#include "stdafx.h"
#include "winAPIPractice.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
HWND g_hwnd;
HDC g_hdc; 

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
	g_hdc = GetDC(g_hwnd);

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
	g_hwnd = hWnd;		// ���� ������ hwnd�� ����
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
#include "SNAKE.h"
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static SNAKE* snake = nullptr;
	static double clock = 0;
	TCHAR str[50] = {'\0'};
	HBRUSH headbrush = (HBRUSH)CreateHatchBrush(HS_DIAGCROSS, RGB(66, 134, 244)); 
	HBRUSH bodybrush, preybrush, oldbrush;
	HPEN silhouette = (HPEN)CreatePen(PS_SOLID, 1.2, RGB(50, 50, 50));
	HPEN oldpen;
	bool msgFlag = false;
	switch (message)
	{
	case WM_CREATE:
	{
		SNAKE::GameWindow(hWnd);
		SetTimer(hWnd, 1, 100, NULL);
		SetTimer(hWnd, 2, 1000, NULL);
		snake = new SNAKE;
	}
	break;
	case WM_TIMER:
	{
		switch (wParam)
		{
		case 1:
			if (!snake->life)
			{
				DestroyWindow(hWnd);
			}
			else
			{
				snake->Update(g_hdc);
				InvalidateRgn(hWnd, NULL, TRUE);
			}

			break;
		case 2:
			clock += 1;
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		}
	}	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// �޴� ������ ���� �м��մϴ�:
		switch (wmId)
		{
		//case IDOK:
		//	msgFlag = false;
		//	delete snake;
		//	snake = new SNAKE();
		//	snake->head.x = 200;
		//	snake->head.y = 200;
		//	break;
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
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
		RECT ui = snake->UI;
			POINT uiPoint[4] = { {snake->UI.left,snake->UI.top},{snake->UI.left,snake->UI.bottom}
			,{snake->UI.right,snake->UI.bottom},{snake->UI.right,snake->UI.top} };
			POINT gameviewPoint[4] = { {snake->gameView.left,snake->gameView.top},{snake->gameView.left,snake->gameView.bottom}
						,{snake->gameView.right,snake->gameView.bottom},{snake->gameView.right,snake->gameView.top} };
			Polygon(g_hdc, uiPoint, 4);
			Polygon(g_hdc, gameviewPoint, 4);


		//oldpen = (HPEN)SelectObject(hdc, (HPEN)silhouette);

		_stprintf_s(str,_countof(str), _T("\n\n\n�ð� : %0.lf\n���� : %d\n"), clock, snake->body.size() + 1);
		DrawText(hdc,str, _tcslen(str), &ui, DT_CENTER);	// DT_SINGLELINE�Ⱦ��� VCENTER �ҿ����
		
		snake->DrawSnake(hdc);
		
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_KEYDOWN:
	{
		if (wParam ==VK_UP && snake->dir != 3)
			snake->dir = 1;
		if (wParam == VK_RIGHT && snake->dir != 4)
			snake->dir = 2;
		if (wParam == VK_DOWN && snake->dir != 1)
			snake->dir = 3;
		if (wParam == VK_LEFT && snake->dir !=2)
			snake->dir = 4;
	}	break;
	case WM_DESTROY:
		DeleteObject((HPEN)silhouette);
		DeleteObject((HBRUSH)headbrush);
		PostQuitMessage(0);
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);

		ReleaseDC(g_hwnd, g_hdc);		// ���� ������ ����ϴ� handler �����ֱ�
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