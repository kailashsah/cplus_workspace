// find_process_list.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once
#include "../pch.h"

#include <fstream> // ifstream
#include <string> // getline()
#include <vector>
using namespace std;

std::vector<CString> Split(CString strSource, CString strDelimiter, unsigned int maxTokens = 0xffffffff, bool bReturnEmptyTokens = true);

inline CString Truncate(CString str, int start);

void GetRunningProcessListUsingTaskList(CStringArray& strProcessList);

bool IsDLLInBlockedlist();


