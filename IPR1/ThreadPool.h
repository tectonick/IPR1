#pragma once
#include <Windows.h>


typedef void (*PFUNC)(void);

class ThreadPool
{
private:
	static const int THREADCOUNT = 5;
	HANDLE * hThreadArray;
	PFUNC * pFuncArray;
	bool * ThreadBusy;

	static DWORD ThreadFunction(LPVOID lpParameter);

public:
	ThreadPool();
	~ThreadPool();
	void Run(PFUNC method);

};

