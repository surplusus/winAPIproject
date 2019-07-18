// winAPIPractice.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
#include "stdafx.h"
#include <tchar.h>
#include "winAPIPractice.h"
#include <Commdlg.h>

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
HWND hwndChild[100];
TCHAR WinBuff[100][1000];
int WndCount;

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
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
	RegisterClassExW(&wcex);
	
	wcex.lpfnWndProc = ChildWndProc;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = _T("Child Window Class Name");
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
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//  �뵵: �� â�� �޽����� ó���մϴ�.
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndClient;
	CLIENTCREATESTRUCT clientcreate;
	MDICREATESTRUCT mdicreate;
	HDC hdc;
	HANDLE hFile;
	static TCHAR filepath[1000], folder[100], filename[100];
	TCHAR filter[] = _T("�ؽ�Ʈ ���� (*.txt)\0*.txt\0��� ���� (*.*)\0*.*\0");
	OPENFILENAME OFN;
	TCHAR InBuff[100];
	TCHAR OutBuff[100] = _T("API ���α׷��� ����ġ �ϳ�!");
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
		// �޴� ������ ���� �м��մϴ�:
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
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...

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