#pragma once
#include <Windows.h>

class BasicThread
{
protected:
	HANDLE m_hThread;		// Window Thread Handle
	DWORD  m_nThreadID;		// Window Thread ID
private:
	BasicThread(const BasicThread& bt) {}					// 해당 Thread의 복제를 막는다
	BasicThread& operator = (const BasicThread& bt) {}	// 해당 Thread의 복제를 막는다
	static DWORD WINAPI StaticThreadStart(LPVOID lpParam);	// 실제 Thread의 시작부분
protected:
	virtual DWORD Run(void) = 0;	// Protected로 사용자가 직접 호출하는 것을 막음
									// 사용하려면 상속해서 Run을 구현해야한다.
public:
	BasicThread() : m_hThread(NULL), m_nThreadID(0){}
	virtual ~BasicThread()	{if (m_hThread) CloseHandle(m_hThread);	}
public:
	bool Start();	// Thread 시작
	void ForceToStop();	// Thread 강제 종료 - 비추!!
public:	// Getter
	inline HANDLE GetThreadHandle() { return m_hThread; }
	inline DWORD GetThreadID() { return m_nThreadID; }

	// Status
	inline bool IsRunning()
	{
		if (m_hThread) {
			DWORD dwExitCode = 0;
			::GetExitCodeThread(m_hThread, &dwExitCode);
			if (dwExitCode == STILL_ACTIVE) return true;
		}
		return false;
	}

	// Join - Wait For Thread Done
	inline void Join()
	{
		::WaitForSingleObject(m_hThread, INFINITE);
	}

	// Yeild - Yeild Execution to Another Thread
	inline BOOL Yeild()
	{
		return ::SwitchToThread();
	}

	// Sleep - Suspends the execution of the current thread until the time-out interval elapses
	inline void Sleep(DWORD dsMilliiseconds)
	{
		::Sleep(dsMilliiseconds);
	}

	// Suspend - Suspend Thread
	inline DWORD Suspend()
	{
		return ::SuspendThread(m_hThread);
	}

	// Resume - Resume Thread
	inline DWORD Resume()
	{
		return ::ResumeThread(m_hThread);
	}
};
