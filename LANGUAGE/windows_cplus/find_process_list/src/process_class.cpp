// find_process_list.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "../pch.h"
#include <pch.h>
#include "process_class.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


inline CString Truncate(CString str, int start)
{
	CString strTrunc = str.Mid(start);
	return strTrunc;
}

/**
*
* Split the given string by the given delimiter and store it into the string
* vector one by one. Calculates the number of tokens found after split
* and store the blank token as well if indicated by the flag.
*
* <b> Input Parameters </b>
*
* strSoruce - CString object contains the source string to be splitted.
* strDelimiter - CString object contains the delimiter to be used to split the
*                 string.
* nMaxTokens - Unsigned integer contains the count of the tokens splitted from
*              the source string.
* bReturnEmptyTokens - Bool to indicate if empty tokens needs to be captured or
*                       not.
*
* <b> Return Value </b>
*
* CString vector contains the tokens.
********************************************************************************/

vector<CString> Split(CString strSource, CString strDelimiter, unsigned int nMaxTokens, bool bReturnEmptyTokens)
{
	strSource.TrimLeft(); strSource.TrimRight();
	vector<CString> vTokens;
	int nPos = 0;
	CString strValue;
	while (vTokens.size() < nMaxTokens - 1 && (nPos = strSource.Find(strDelimiter)) != -1)
	{
		strValue = strSource.Left(nPos); strValue.TrimLeft(); strValue.TrimRight();
		if (strValue.IsEmpty())
		{
			if (bReturnEmptyTokens)
				vTokens.push_back(strValue);
		}
		else
			vTokens.push_back(strValue);

		strSource = Truncate(strSource, nPos + strDelimiter.GetLength()); strSource.TrimLeft(); strSource.TrimRight();
	}
	if (!strSource.IsEmpty())
		vTokens.push_back(strSource);
	return vTokens;
}

void GetRunningProcessListUsingTaskList(CString& strProcessList)
{
	try
	{
		TCHAR tcCmdPath[MAX_PATH];
		FindExecutable(L"cmd.exe", NULL, tcCmdPath);

		TCHAR tcTempPath[MAX_PATH];
		GetTempPath(MAX_PATH, tcTempPath);
		_tcscat(tcTempPath, _T("ProcessList.txt"));

		TCHAR tcProcessParam[MAX_PATH];
		_tcscpy(tcProcessParam, _T("/K tasklist.exe >> "));
		_tcscat(tcProcessParam, tcTempPath);

		STARTUPINFO         siStartupInfo;
		PROCESS_INFORMATION piProcessInfo;

		memset(&siStartupInfo, 0, sizeof(siStartupInfo));
		memset(&piProcessInfo, 0, sizeof(piProcessInfo));

		siStartupInfo.cb = sizeof(siStartupInfo);
		siStartupInfo.dwFlags |= STARTF_USESHOWWINDOW;
		siStartupInfo.wShowWindow = SW_HIDE;

		CreateProcess(tcCmdPath,
			tcProcessParam,                 // Application arguments 
			0,
			0,
			FALSE,
			CREATE_DEFAULT_ERROR_MODE,
			0,
			0,                              // Working directory 
			&siStartupInfo,
			&piProcessInfo);

		if (piProcessInfo.hProcess == NULL)
			return;

		::Sleep(1000);

		FILE* stream;
		if ((stream = freopen((char*)tcTempPath, "w", stdout)) == NULL)
			return;

		//stream = freopen("CON", "w", stdout);

		string STRING;
		ifstream infile;
		infile.open(tcTempPath);
		int a = 0;
		string previousLine = "";
		//Skip these three lines which contains the header information
		getline(infile, STRING); // Saves the line in STRING.
		getline(infile, STRING); // Saves the line in STRING.
		getline(infile, STRING); // Saves the line in STRING.

		while (getline(infile, STRING)) // To get you all the lines.
		{
			if (STRING != previousLine)
			{
				previousLine = STRING;
				vector<CString> vstr = ::Split(CString(STRING.c_str()), L" ");
				if (vstr.size() > 0)
				{
					strProcessList += vstr[0] + L" "/* delimiter */;
				}
			}
		}
		infile.close();
		DeleteFile(tcTempPath);
		//TerminateProcess(piProcessInfo.hProcess, 1);
	}
	catch (CMemoryException* e)
	{
		strProcessList += _T("CMemoryException in GetRunningProcessListUsingTaskList");
		e->Delete();
	}
	catch (CFileException* e)
	{
		strProcessList += _T("CFileException in GetRunningProcessListUsingTaskList");
		e->Delete();
	}
	catch (CException* e)
	{
		strProcessList += _T("CException in GetRunningProcessListUsingTaskList");
		e->Delete();
	}
}


bool IsDLLInBlockedlist()
{
	/*
		this function checks if block list dll exist in process memory
	*/
	bool isBlockedDllfound = false;
	CStringA	configName;
	CString strMessageText;

	CString strBlockedDLLs = L"helper.dll,translate.dll";
	vector<CString> vecBlockedDLLs;
	vecBlockedDLLs = ::Split(strBlockedDLLs, L",");
	int nSize = vecBlockedDLLs.size();
	if (nSize <= 0)
		return false;
	CString strDLL;
	for (int i = 0; i < nSize; i++)
	{
		strDLL = vecBlockedDLLs[i];
		if (strDLL.IsEmpty())
			continue;
		HMODULE hModule = GetModuleHandle(strDLL);
		if (hModule)
		{
			/*
			TCHAR lpszModule[_MAX_PATH];
			GetModuleFileName(hModule, lpszModule, _MAX_PATH);
			wprintf(lpszModule);

			*/
			isBlockedDllfound = true;
			break;
		}
	}
	return isBlockedDllfound;
}
#include "CpuInfo.h"
#include "tlhelp32.h"	// window tools help PROCESSENTRY32
#include "psapi.h"		//CREATETOOLHELP32SNAPSHOTFUNC
#undef LPPROCESSENTRY32
#undef LPMODULEENTRY32
#undef PROCESSENTRY32
#undef MODULEENTRY32
typedef HANDLE(CALLBACK* CREATETOOLHELP32SNAPSHOTFUNC)(DWORD dwFlags, DWORD th32ProcessID);
typedef BOOL(CALLBACK* PROCESS32FIRSTFUNC)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
typedef BOOL(CALLBACK* PROCESS32NEXTFUNC)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
typedef BOOL(CALLBACK* GETPROCESSMEMORY)(HANDLE hProcess, PPROCESS_MEMORY_COUNTERS ppsmemCounters, DWORD cb);
BOOL LogApplicationsRunning()
{
	/*OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	if ((::GetVersionEx(&osvi)) == 0) return FALSE;

	if (osvi.dwPlatformId != VER_PLATFORM_WIN32_NT)
		return FALSE;
	else if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT && osvi.dwMajorVersion <= 4)
		return FALSE;*/

	HANDLE hSnapShot;
	PROCESSENTRY32 pEntry;

	pEntry.dwSize = sizeof(pEntry);

	CREATETOOLHELP32SNAPSHOTFUNC pCreateToolhelp32Snapshot = NULL;
	PROCESS32FIRSTFUNC pProcess32First = NULL;
	PROCESS32NEXTFUNC pProcess32Next = NULL;

	HINSTANCE m_hKernel32Dll = LoadLibrary(_T("Kernel32.dll"));
	HINSTANCE m_hPsApiDll = LoadLibrary(_T("PSAPI.dll"));

	pCreateToolhelp32Snapshot = (CREATETOOLHELP32SNAPSHOTFUNC)GetProcAddress(m_hKernel32Dll, "CreateToolhelp32Snapshot");
	pProcess32First = (PROCESS32FIRSTFUNC)GetProcAddress(m_hKernel32Dll, "Process32First");
	pProcess32Next = (PROCESS32NEXTFUNC)GetProcAddress(m_hKernel32Dll, "Process32Next");

	if (pCreateToolhelp32Snapshot == NULL || pProcess32First == NULL || pProcess32Next == NULL)
		return FALSE;

	//Get the snapshot of the system
	hSnapShot = pCreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	if (hSnapShot == INVALID_HANDLE_VALUE)
		return FALSE;

	//Get first process
	BOOL bFlag = pProcess32First(hSnapShot, &pEntry);
	CString strLog, strTemp;
	
	while (bFlag)
	{
		CpuInfo usageA;
		usageA.GetCpuUsage(pEntry.th32ProcessID);

		strTemp.Format(_T("%s,"), pEntry.szExeFile);
		strLog += strTemp;

		int nCpuUsage = 0;
		int nMemUsage = 0;

		// Retrieve the priority class.
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
			PROCESS_VM_READ, FALSE, pEntry.th32ProcessID);
		if (hProcess != NULL)
		{
			PROCESS_MEMORY_COUNTERS psCounter;
			memset(&psCounter, 0, sizeof(psCounter));
			if (m_hPsApiDll != NULL)
			{
				//GetProcessMemoryInfo(hProcess, &psCounter, sizeof(psCounter));
				GETPROCESSMEMORY pGetProcessMemory = NULL;
				pGetProcessMemory = (GETPROCESSMEMORY)GetProcAddress(m_hPsApiDll, "GetProcessMemoryInfo");
				if (pGetProcessMemory != NULL)
				{
					pGetProcessMemory(hProcess, &psCounter, sizeof(psCounter));
				}
			}

			nMemUsage = psCounter.WorkingSetSize / 1024;

			CloseHandle(hProcess);
		}

		nCpuUsage = usageA.GetCpuUsage(pEntry.th32ProcessID);

		strTemp.Format(_T("%d,%d%%,%dKB;"), pEntry.cntThreads, nCpuUsage, nMemUsage);
		strLog += strTemp;

		//Iterate thru all processes
		BOOL hRes = pProcess32Next(hSnapShot, &pEntry);
		if (hRes == FALSE)
		{
			bFlag = FALSE;
			break;
		}
	}

	wprintf(L"%s", strLog.GetString());
	return bFlag;
}
