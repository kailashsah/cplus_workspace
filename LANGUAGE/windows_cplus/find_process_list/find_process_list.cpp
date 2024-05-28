// find_process_list.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "find_process_list.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "src/process_class.h" 
// The one and only application object

CWinApp theApp;
#include <future>
#include <thread>
void driverCode();
int main()
{
    int nRetCode = 0;
    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // initialize MFC and print and error on failure
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: code your application's behavior here.
            wprintf(L"Fatal Error: MFC initialization failed\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: code your application's behavior here.
            driverCode();
        }
    }
    else
    {
        // TODO: change error code to suit your needs
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        nRetCode = 1;
    }
	wprintf(L"at the end\n");

    return nRetCode;
}

void driverCode()
{
    CStringArray strProcessList;

    auto fut = async(launch::async, [&]() { GetRunningProcessListUsingTaskList(strProcessList); });
    //GetRunningProcessListUsingTaskList(strProcessList);
    fut.get();
    
    //wprintf(L"%s \n", strProcessList.GetString()); // not printing
    
    //AfxMessageBox(strProcessList));
}
