#pragma once
#include <Windows.h>

class BasicThread
{
protected:
	HANDLE m_hThread;		// Window Thread Handle
	DWORD  m_nThreadID;		// Window Thread ID
private:
	BasicThread(const BasicThread& bt) {}					// �ش� Thread�� ������ ���´�
	BasicThread& operator = (const BasicThread& bt) {}	// �ش� Thread�� ������ ���´�
	static DWORD WINAPI StaticThreadStart(LPVOID lpParam);	// ���� Thread�� ���ۺκ�
protected:
	virtual DWORD Run(void) = 0;	// Protected�� ����ڰ� ���� ȣ���ϴ� ���� ����
									// ����Ϸ��� ����ؼ� Run�� �����ؾ��Ѵ�.
public:
	BasicThread() : m_hThread(NULL), m_nThreadID(0){}
	virtual ~BasicThread()	{if (m_hThread) CloseHandle(m_hThread);	}
public:
	bool Start();	// Thread ����
	void ForceToStop();	// Thread ���� ���� - ����!!
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
