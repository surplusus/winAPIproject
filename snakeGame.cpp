// winAPIPractice.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
#include "stdafx.h"
#include "winAPIPractice.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hwnd;
HDC g_hdc; 

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINAPIPRACTICE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIPRACTICE));
	MSG msg;
	g_hdc = GetDC(g_hwnd);

	// 기본 메시지 루프입니다:
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

//  함수: MyRegisterClass()
//  용도: 창 클래스를 등록합니다.
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

//   함수: InitInstance(HINSTANCE, int)
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//   주석:
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}
	g_hwnd = hWnd;		// 전역 변수에 hwnd를 복사
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}
//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//  용도: 주 창의 메시지를 처리합니다.
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
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
		// 메뉴 선택을 구문 분석합니다:
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
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		RECT ui = snake->UI;
			POINT uiPoint[4] = { {snake->UI.left,snake->UI.top},{snake->UI.left,snake->UI.bottom}
			,{snake->UI.right,snake->UI.bottom},{snake->UI.right,snake->UI.top} };
			POINT gameviewPoint[4] = { {snake->gameView.left,snake->gameView.top},{snake->gameView.left,snake->gameView.bottom}
						,{snake->gameView.right,snake->gameView.bottom},{snake->gameView.right,snake->gameView.top} };
			Polygon(g_hdc, uiPoint, 4);
			Polygon(g_hdc, gameviewPoint, 4);


		//oldpen = (HPEN)SelectObject(hdc, (HPEN)silhouette);

		_stprintf_s(str,_countof(str), _T("\n\n\n시간 : %0.lf\n꼬리 : %d\n"), clock, snake->body.size() + 1);
		DrawText(hdc,str, _tcslen(str), &ui, DT_CENTER);	// DT_SINGLELINE안쓰면 VCENTER 소용없다
		
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

		ReleaseDC(g_hwnd, g_hdc);		// 전역 변수로 사용하던 handler 없애주기
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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