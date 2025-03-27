
#include <iostream>
#include<string>
using namespace std;
//#define _CRT_SECURE_NO_WARNINGS // for localtime


/*
	1. this code is for test output purpose only.
	2. It works on pointer movement that looks doubtful if like to refactor with smart pointers or string class.
*/

int FormatDateTimeSpecification(char* pIn, char* pOut, int nMaxLen);
int main()
{
	int  maxLen = 1024 + 2;
	char szParameters[1024 + 2];


	//string str= "#%m%d%Y#.dat";           // "03172025.dat"           # at both ends
	//string str= "#%m%d%Y##.dat";          // "03172025#.dat"          adds # last if extra given
	//string str= "#%m%d%Y##%m%d%Y#.dat";   // "0317202503172025.dat"   correct if # symmetry
	//string str = "#%maaa%d%Y#.dat";        //03aaa182025.dat          mixed with char literals


	//--FALSE CASES--
	//string str = "#%m%d%Y#%m%d%Y#.dat";   //"03172025%m%d%Y#.dat"     if single # in between
	//string str = "#%m%d%Y#%m%d%Y##%m%d%Y#.dat";   //03182025%m%d%Y#%m%d%Y#.dat     it shuld have  "#%m%d%Y# #%m%d%Y##%m%d%Y#.dat"
	//string str= "#%m%d%Y.dat";            // "#%m%d%Y.dat"            # not given at last
	//string str= "#%m'aaa'%d%Y.dat";       // #%m'aaa'%d%Y.dat         mixed with char literals with ' quotes
	//string str= "#%m#.dat";       //03.dat
	//string str= "##%m#";       //#%m#
	//string str= "##%maada%d%y#";       // #%maadaa%d%y# 


	FormatDateTimeSpecification((char*)str.data(), szParameters, maxLen);
	std::cout << "Hello World!\n";
}

int FormatDateTimeSpecification(char* pIn, char* pOut, int nMaxLen)
{
	time_t Now;         // Current DateTime
	struct tm* pToday;  // TimeDate Structure
	int   nWork;        // Work Value
	char* pWork;        // Work pointer
	const char* pProbe; // Probe pointer
	char* pFmt;         // Format String pointer
	int   nFmtLen;      // Format Length

	time(&Now);
	pToday = localtime(&Now);

	nMaxLen--;                              // Adjust for trailing \0

	for (pWork = pOut; *pIn && nMaxLen > 0; pIn++)
	{
		/*
		**+
		**  First, check for non-pound or double pound.  Copy
		**  them and continue.
		**-
		*/

		if (*pIn != L'#')
		{
			*pWork++ = *pIn;
			nMaxLen--;
			continue;
		}

		pIn++;
		if (*pIn == L'#')
		{
			*pWork++ = L'#';
			nMaxLen--;
			continue;
		}

		/*
		**+
		**  This is a single-pound string.  Look for the ending pound.
		**-
		*/

		for (pProbe = pIn; *pProbe && *pProbe != L'#'; pProbe++);

		/*
		**+
		**  Non-pound ending found, copy pound and continue.
		**-
		*/

		if (*pProbe == NULL)
		{
			*pWork++ = L'#';
			*pWork++ = *pIn;
			nMaxLen -= 2;
			continue;
		}


		nFmtLen = (int)(pProbe - pIn);              //pProbe = #.dat pIn = %m%d%Y#.dat   nFmtLen = 6
		pFmt = (char*)malloc((nFmtLen * sizeof(char)) + sizeof(char));
		if (!pFmt)
			break;
		memcpy((char*)pFmt, (const char*)pIn, nFmtLen);
		pFmt[nFmtLen] = '\0';                      // %m%d%Y
		//LOGIF(VERB, DBG, L"Passing %s to wcsftime", pFmt);
		nWork = (int)strftime((char*)pWork, nMaxLen, (const char*)pFmt, pToday);
		//LOGIF(VERB, DBG, L"Back from wcsftime");
		free(pFmt);
		if (nWork == 0)
		{
			int nErrNum = errno;
			if (nErrNum == EINVAL)
				return -1;
		}
		if (nWork)
			pWork += nWork;
		else
			*pWork = 0;
		pIn += nFmtLen;
		nMaxLen -= nWork;
	}

	*pWork = L'\0';
	return 0;
}