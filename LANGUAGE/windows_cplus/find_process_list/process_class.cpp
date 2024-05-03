// find_process_list.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
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


