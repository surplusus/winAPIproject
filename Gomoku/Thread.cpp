#include "stdafx.h"
#include "Thread.h"

DWORD __stdcall BasicThread::StaticThreadStart(LPVOID lpParam)
{
	BasicThread* pThread = (BasicThread*)lpParam;
	return pThread->Run();
}

bool BasicThread::Start()
{
	if (m_hThread) // �̹� Thread�� �����Ǿ� �ִ� ���
	{
		if (WaitForSingleObject(m_hThread, 0) == WAIT_TIMEOUT) {	// Thread Still Running
			return false;	// Start �ź�
		}
		CloseHandle(m_hThread);
	}

	// Thread ����
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
		// ���� Terminate�̹Ƿ� �������� �ڿ� ������ ����� �� ����
		// �����ڿ� ���� ���� ���� ��� deadlock ���� ������ ���� �� ����
		::TerminateThread(m_hThread, -1);
	}

	if (m_hThread) {
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
}

///////////////////// ��� ����//////////////////////////
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
//}    /////////////////// ��� ����//////////////////////////