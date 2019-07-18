// Socket_Server.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Socket_Server.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include <stdio.h>

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
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_SOCKETSERVER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SOCKETSERVER));
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
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SOCKETSERVER));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SOCKETSERVER);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassExW(&wcex);
}
//
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
//
#include <deque>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static WSADATA wsadata;
	static SOCKET s, cs[4];
	static int idxcs = 0;
	static TCHAR msg[200];
	static char buffer[100];
	static SOCKADDR_IN addr = { 0 }, c_addr;
	static TCHAR str[100];
	static int count;
	int size, msglen;
	int client_alive_flag[4] = { 0, };
	static std::deque<TCHAR*> chat_list;
	static int cnt_msg = 0;

	switch (message)
	{
	case WM_CREATE:
	{
		SetTimer(hWnd, 1, 5000, NULL);
		MoveWindow(hWnd, 50, 50, 400, 500, TRUE);
		WSAStartup(MAKEWORD(2, 2), &wsadata);	//2.2는 실수이므로 MAKEWORD로 WORD(unsigned short)으로 형변환
		s = socket(AF_INET, SOCK_STREAM, 0);
		addr.sin_family = AF_INET;
		addr.sin_port = 20;
		inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.S_un.S_addr);
		bind(s, (LPSOCKADDR)&addr, sizeof(addr));
		WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_ACCEPT);
		if (listen(s, 5) == -1)	return 0;
	}	break;
	case WM_ASYNC:
	{
		switch (lParam)
		{
		case FD_ACCEPT:
		{
			size = sizeof(c_addr);
			for (int i = 0; i < 5; ++i)
			{
				if (i == 4)
				{
					TCHAR *endsign = new TCHAR[30];
					_tcscpy_s(endsign,30, _T("챗방에 사람이 꽉 찼습니다. 못 들어와요."));
					chat_list.push_back(endsign);
				}
				if (cs[i] == 0)
				{
					cs[i] = accept(s, (LPSOCKADDR)&c_addr, &size);
					TCHAR *endsign = new TCHAR[30];
					_tcscpy_s(endsign, 30, _T("새로운 사람이 들어왔습니다."));
					chat_list.push_back(endsign);
					break;
				}
			}

			//rc = WSAAsyncSelect(s, hWnd, (메시지), (이벤트속성)FD_READ|FD_WRITE);
			WSAAsyncSelect(cs[idxcs++], hWnd, WM_ASYNC, FD_READ);
			InvalidateRgn(hWnd, NULL, TRUE);
		}	break;
		case FD_READ:
		{
			for (int i = 0; i < 4; ++i)
			{
				msglen = recv(cs[i], buffer, 100, 0);
				if (cs[i] != 0 && msglen != -1)
				{
					client_alive_flag[i] = 1;
					break;
				}
			}
			buffer[msglen] = NULL;
#ifdef _UNICODE
			msglen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);
			MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), msg, msglen);
			msg[msglen] = NULL;
#else
			strcpy_s(msg, buffer);
#endif // _UNICODE
			TCHAR* tmp = new TCHAR[msglen];
			swprintf_s(tmp, sizeof(TCHAR)*msglen, _T("%s"), msg);
			chat_list.push_back(tmp);
			InvalidateRgn(hWnd, NULL, TRUE);
		}	break;
		}
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		
		while (true)
		{
			if (chat_list.size() > 3)
			{
				auto tmp = chat_list.front();
				chat_list.pop_front();
				delete tmp;
			}
			else
				break;
		}

		auto chat = chat_list.begin();
		int chatline = 0;
		while (chat != chat_list.end())
		{
			_tcscpy_s(msg,_countof(msg),(const wchar_t*)*chat);
			TextOut(hdc, 10, chatline * 15, (LPCWSTR)msg, _tcslen(msg));
			chat++;
			chatline++;
		}
		EndPaint(hWnd, &ps);

	}	break;
	case WM_TIMER:
	{
		for (int i = 0; i < 4; ++i)
		{
			if (cs[i] == 0)
			{
				continue;
			}
			client_alive_flag[i]++;
			if (client_alive_flag[i] > 100)
				cs[i] = 0;

			auto chat = chat_list.begin();
			while (chat != chat_list.end())
			{
				_tcscpy_s(str, sizeof(TCHAR)*_tcslen(*chat), (const wchar_t*)(*chat));
#ifdef _UNICODE
				msglen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_ACP, 0, str, -1, buffer, msglen, NULL, NULL);
#else
				strcpy_s(buffer, str);
#endif // _UNICODE
				buffer[_tcslen(str)] = NULL;

				send(cs[i], (LPSTR)buffer, strlen(buffer) + 1, 0);
				chat++;
			}
		}
		return 0;
	}	break;
	case WM_GETMINMAXINFO:
	{
		((MINMAXINFO *)lParam)->ptMaxTrackSize.x = 400;
		((MINMAXINFO *)lParam)->ptMaxTrackSize.y = 500;
		((MINMAXINFO *)lParam)->ptMinTrackSize.x = 400;
		((MINMAXINFO *)lParam)->ptMinTrackSize.y = 500;
		return FALSE;
	}	break;
	case WM_DESTROY:
	{
		auto chat = chat_list.begin();
		while (chat != chat_list.end())
		{
			delete *chat;
			chat++;
		}
		closesocket(s);
		WSACleanup();
		PostQuitMessage(0);
	}	break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
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