#include "stdafx.h"
#include "Thread.h"

DWORD __stdcall BasicThread::StaticThreadStart(LPVOID lpParam)
{
	BasicThread* pThread = (BasicThread*)lpParam;
	return pThread->Run();
}

bool BasicThread::Start()
{
	if (m_hThread) // 이미 Thread가 생성되어 있는 경우
	{
		if (WaitForSingleObject(m_hThread, 0) == WAIT_TIMEOUT) {	// Thread Still Running
			return false;	// Start 거부
		}
		CloseHandle(m_hThread);
	}

	// Thread 생성
	m_hThread = CreateThread(
		NULL,			// default security attributes
		0,				// default stack size
		(LPTHREAD_START_ROUTINE)BasicThread::StaticThreadStart,
		this,			// thread function argument = this class
		0,				// default creation flags
		&m_nThreadID	// receive thread identifier
	);

	if (m_hThread != NULL) return true;

	return false;
}

void BasicThread::ForceToStop()
{
	if (this->IsRunning()) {
		// 강제 Terminate이므로 정상적인 자원 해제를 기대할 수 없음
		// 공유자원 등을 물고 있을 경우 deadlock 등의 위험이 있을 수 있음
		::TerminateThread(m_hThread, -1);
	}

	if (m_hThread) {
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
}

///////////////////// 사용 예제//////////////////////////
//{
//#include <stdio.h>
//#include "BasicThread.h"
//
//	class TestThread : public BasicThread
//	{
//	protected:
//		DWORD Run(void)
//		{
//			printf("Thread %d Start\n", GetThreadID());
//
//			for (int i = 0; i < 5; i++)
//			{
//				printf("Thread %d : Count %d\n", GetThreadID(), i);
//				this->Sleep(1000);
//			}
//
//			printf("Thread %d End\n", GetThreadID());
//
//			return 0;
//		}
//	};
//
//	int main(void)
//	{
//		TestThread* pThread[5];
//
//		for (int i = 0; i < 5; i++)
//		{
//			pThread[i] = new TestThread();
//			pThread[i]->Start();
//		}
//
//		for (int i = 0; i < 5; i++)
//		{
//			pThread[i]->Join(); // wait for thread  done
//			delete pThread[i];	// if done, end thread
//		}
//
//		return 0;
//	}
//
//}    /////////////////// 사용 예제//////////////////////////