// winAPIPractice.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
#include "stdafx.h"
#include <tchar.h>
#include "winAPIPractice.h"
#include <Commdlg.h>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND hwndChild[100];
TCHAR WinBuff[100][1000];
int WndCount;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ChildWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void ReadFromFile(int WndIndex, TCHAR filename[]);

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
	RegisterClassExW(&wcex);
	
	wcex.lpfnWndProc = ChildWndProc;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = _T("Child Window Class Name");
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
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd)
	{
		return FALSE;
	}
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndClient;
	CLIENTCREATESTRUCT clientcreate;
	MDICREATESTRUCT mdicreate;
	HDC hdc;
	HANDLE hFile;
	static TCHAR filepath[1000], folder[100], filename[100];
	TCHAR filter[] = _T("텍스트 파일 (*.txt)\0*.txt\0모든 파일 (*.*)\0*.*\0");
	OPENFILENAME OFN;
	TCHAR InBuff[100];
	TCHAR OutBuff[100] = _T("API 프로그래밍 조까치 하네!");
	DWORD size;
	RECT rt;

	switch (message)
	{
	case WM_CREATE:
	{
		clientcreate.hWindowMenu = GetSubMenu(GetMenu(hWnd), 0);
		clientcreate.idFirstChild = 100;
		hwndClient = CreateWindow(_T("MDICLIENT"), NULL, WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
			0, 0, 0, 0, hWnd, NULL, hInst, (LPSTR)&clientcreate);
		ShowWindow(hwndClient, SW_SHOW);
		return 0;
	}	break;
	
	case WM_LBUTTONDOWN:
	{
		hFile = CreateFile(_T("test1.txt"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
		memset(InBuff, 0, sizeof(InBuff));
		ReadFile(hFile, InBuff, 999 * sizeof(TCHAR), &size, NULL);
		hdc = GetDC(hWnd);
		GetClientRect(hWnd, &rt);
		DrawText(hdc, InBuff, (int)_tcslen(InBuff), &rt, DT_TOP | DT_LEFT);
		ReleaseDC(hWnd, hdc);
		WriteFile(hFile, OutBuff, (DWORD)_tcslen(OutBuff) * sizeof(TCHAR), &size, NULL);
		CloseHandle(hFile);
	}	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
			case ID_FILEOPEN:
	{
		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = hWnd;
		OFN.lpstrFile = filepath;
		OFN.nMaxFileTitle = 100;
		OFN.lpstrFileTitle = filename;
		OFN.nMaxFile = 1000;
		OFN.lpstrFilter = filter;
		OFN.Flags = OFN_EXPLORER;
		GetOpenFileName(&OFN);
		WndCount++;
		ReadFromFile(WndCount, filepath);
		mdicreate.szClass = _T("Child Window Class Name");
		mdicreate.szTitle = filepath;
		mdicreate.hOwner = hInst;
		mdicreate.x = CW_USEDEFAULT;
		mdicreate.y = CW_USEDEFAULT;
		mdicreate.cx = CW_USEDEFAULT;
		mdicreate.cy = CW_USEDEFAULT;
		mdicreate.style = 0;
		mdicreate.lParam = 0;
		hwndChild[WndCount] = (HWND)SendMessage(hwndClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mdicreate);
		return 0;
	}	break;
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

		EndPaint(hWnd, &ps);
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

LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i, SelectWnd;
	HDC hdc;
	RECT rt;
	PAINTSTRUCT ps;
	for (i = 1; i<=WndCount;++i)
		if (hWnd = hwndChild[i])
		{
			SelectWnd = i;
			break;
		}
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rt);
		DrawText(hdc, WinBuff[SelectWnd], (int)_tcsclen(WinBuff[SelectWnd]), &rt, DT_TOP | DT_LEFT);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		return 0;
	}
	return DefMDIChildProc(hWnd, message, wParam, lParam);
}

void ReadFromFile(int WndIndex, TCHAR filename[])
{
	HANDLE hFile;
	DWORD size = 1000;
	hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
	ReadFile(hFile, WinBuff[WndIndex], size * sizeof(TCHAR), &size, NULL);
	WinBuff[WndIndex][size] = NULL;
	CloseHandle(hFile);
}