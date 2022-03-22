#include "ThreadPool.h"
#include <Windows.h>
#include <iostream>

typedef struct
{
    int id;
    bool* busyCounter;
    PFUNC* method;
    HANDLE* threadHandle;
} ThreadData;



DWORD ThreadPool::ThreadFunction(LPVOID lpParameter)
{

    ThreadData * td = (ThreadData*)lpParameter;

    PFUNC* method = td->method;
    if ((* method) != NULL) {
        (*method)();
        *(td->busyCounter) = false;
        *(td->method) = NULL;

        //HANDLE hCurrentThread = *(td->threadHandle);
        *(td->threadHandle) = CreateThread(
            NULL,
            0,
            ThreadFunction,
            td,
            CREATE_SUSPENDED,
            NULL);
        ExitThread(0);
    }
    return 0;
}


ThreadPool::ThreadPool()
{
    pFuncArray = (PFUNC*)malloc(sizeof PFUNC * THREADCOUNT);
    hThreadArray = (HANDLE*)malloc(sizeof HANDLE * THREADCOUNT);
    ThreadBusy= (bool*)malloc(THREADCOUNT);
	for (int i = 0; i < THREADCOUNT; i++)
	{
        ThreadBusy[i] = false;
        pFuncArray[i] = NULL;
        ThreadData * td = new ThreadData;
        td->id = i;
        td->busyCounter = &ThreadBusy[i];
        td->method = &pFuncArray[i];
        td->threadHandle = &hThreadArray[i];
        hThreadArray[i] = CreateThread(
            NULL,                   
            0,                       
            ThreadFunction,       
            td,    
            CREATE_SUSPENDED,
            NULL); 
	}
}

ThreadPool::~ThreadPool()
{
    for (int i = 0; i < THREADCOUNT; i++)
    {
        ResumeThread(hThreadArray[i]);
        WaitForSingleObject(hThreadArray[i],INFINITE);
        CloseHandle(hThreadArray[i]);
    }
}

void ThreadPool::Run(PFUNC method)
{
    while (true) {
        for (int i = 0; i < THREADCOUNT; i++)
        {
            if (!ThreadBusy[i]) {
                ThreadBusy[i] = true;
                pFuncArray[i] = method;
                int status = ResumeThread(hThreadArray[i]);
                if (status == -1) {
                    std::cout << "Error resuming thread!\n";
                }
                return;
            }
        }
        Sleep(1);
    }
}
