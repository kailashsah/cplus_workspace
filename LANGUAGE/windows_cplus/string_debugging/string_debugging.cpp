// string_debugging.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//#define _CRT_SECURE_NO_WARNINGS // for localtime

int FormatDateTimeSpecification(char* pIn, char* pOut, int nMaxLen);
int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

int FormatDateTimeSpecification(char* pIn, char* pOut, int nMaxLen)
{
    time_t      Now;                        // Current DateTime
    struct tm* pToday;                    // TimeDate Structure
    int       nWork;                      // Work Value
    char* pWork;                     // Work pointer
    const char* pProbe;                    // Probe pointer
    char* pFmt;                      // Format String pointer
    int       nFmtLen;                    // Format Length

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


        nFmtLen = (int)(pProbe - pIn);
        pFmt = (char*)malloc((nFmtLen * sizeof(char)) + sizeof(char));
        if (!pFmt)
            break;
        wmemcpy((wchar_t*)pFmt, (const wchar_t*)pIn, nFmtLen);
        pFmt[nFmtLen] = L'\0';
        //LOGIF(VERB, DBG, L"Passing %s to wcsftime", pFmt);
        nWork = (int)wcsftime((wchar_t*)pWork, nMaxLen, (const wchar_t*)pFmt, pToday);
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