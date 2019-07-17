// Socket_Client.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Socket_Client.h"
#include <tchar.h>
#include <stdio.h>
#include <WS2tcpip.h>
#include <WinSock2.h>
#pragma comment (lib, "ws2_32.lib")

#define MAX_LOADSTRING 100
#define WM_ASYNC WM_USER+2
// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
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
	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_SOCKETCLIENT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	// 응용 프로그램 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SOCKETCLIENT));
	MSG msg;
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

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SOCKETCLIENT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SOCKETCLIENT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static WSADATA wsadata;
	static SOCKET s;
	static TCHAR msg[200];
	static char buffer[100];
	static SOCKADDR_IN addr = { 0 };
	static TCHAR str[100];
	static int count;
	int size, msglen;

	switch (message)
	{
	case WM_CREATE:
	{
		MoveWindow(hWnd, 600, 50, 400, 100, TRUE);
		WSAStartup(MAKEWORD(2, 2), &wsadata);
		s = socket(AF_INET, SOCK_STREAM, 0);
		addr.sin_family = AF_INET;
		addr.sin_port = 20;
		inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.S_un.S_addr);
		bind(s, (LPSOCKADDR)&addr, sizeof(addr));
		WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_ACCEPT | FD_READ);
		if (connect(s, (LPSOCKADDR)&addr, sizeof(addr)) == -1)	return 0;
	}	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		if (_tcscmp(msg, _T("")))
			TextOut(hdc, 0, 30, msg, (int)_tcslen(msg));
		EndPaint(hWnd, &ps);
	}	break;
	case WM_ASYNC:
	{
		switch (lParam)
		{
		case FD_READ:
		{
			msglen = recv(s, buffer, 100, 0);
			buffer[msglen] = NULL;
			send(s, buffer, msglen, 0);
#ifdef _UNICODE
			msglen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);
			MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), msg, msglen);
			msg[msglen] = NULL;
#else
			strcpy_s(msg, buffer);
#endif // _UNICODE
			InvalidateRgn(hWnd, NULL, TRUE);
		}break;
		default:
			break;
		}
	}	break;
	case WM_CHAR:
	{
		if (wParam == VK_RETURN)
			if (s == INVALID_SOCKET)
				return 0;
			else
			{
#ifdef _UNICODE
				msglen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_ACP, 0, str, -1, buffer, msglen, NULL, NULL);
#else
				strcpy_s(buffer, str);
				msglen = strlen(buffer);
#endif // _UNICODE
				send(s, (LPSTR)buffer, msglen + 1, 0);
				count = 0;
				return 0;
			}
		str[count++] = wParam;
		str[count] = NULL;
		InvalidateRgn(hWnd, NULL, TRUE);
		return 0;
	}	break;
	case WM_GETMINMAXINFO:
	{
		((MINMAXINFO *)lParam)->ptMaxTrackSize.x = 400;
		((MINMAXINFO *)lParam)->ptMaxTrackSize.y = 100;
		((MINMAXINFO *)lParam)->ptMinTrackSize.x = 400;
		((MINMAXINFO *)lParam)->ptMinTrackSize.y = 100;
		return FALSE;
	}	break;
	case WM_DESTROY:
	{
		closesocket(s);
		WSACleanup();
		PostQuitMessage(0);
	}	break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

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
