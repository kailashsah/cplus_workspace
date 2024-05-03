#ifndef _CPUUSAGE_H
#define _CPUUSAGE_H

#include <windows.h>
#include <pdh.h>
#include <pdhmsg.h>
#include <iostream>
using namespace std;
#define CPU_USAGE "\\Processor(_Total)\\% Processor Time"

typedef struct CounterStruct {
	LONG lValue;			// The current value of this counter
    HCOUNTER hCounter;      // Handle to the counter - given to use by PDH Library
} CounterStruct, *PCounterStruct;

class CpuInfo
{
public:
	CpuInfo();
	virtual ~CpuInfo();

// Methods
	int GetCpuUsage();
	int GetCpuUsage(LPCTSTR pProcessName);
	int GetCpuUsage(DWORD dwProcessID);

	BOOL EnablePerformaceCounters(BOOL bEnable = TRUE);

// Attributes
private:
	bool			m_bFirstTime;
	LONGLONG		m_lnOldValue ;
	LARGE_INTEGER	m_OldPerfTime100nSec;
};


#endif