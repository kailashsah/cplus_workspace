#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
/*
	1. Split the given string by the given delimiter and store it into the string
	 vector one by one. Calculates the number of tokens found after split
	 and store the blank token as well if indicated by the flag.  

	 <b> Input Parameters </b>

	 strSoruce - CString object contains the source string to be splitted.
	 strDelimiter - CString object contains the delimiter to be used to split the
					 string.
	 nMaxTokens - Unsigned integer contains the count of the tokens splitted from 
				  the source string.
	 bReturnEmptyTokens - Bool to indicate if empty tokens needs to be captured or
						   not.
 
	 <b> Return Value </b>

	 string vector contains the tokens.

*/

//
vector<string> SplitDelimiterLine(string strSource, string strDelimiter, unsigned int nMaxTokens, bool bReturnEmptyTokens = false);

//
vector<string> SplitDelimiterLine(string strSource, string strDelimiter, unsigned int nMaxTokens, bool bReturnEmptyTokens)
{
	vector<string> vTokens;
	if (strSource.empty())
		return vTokens;
	//strSource.TrimLeft(); strSource.TrimRight();
	int nPos = 0;
	string strValue;
	while (vTokens.size() < nMaxTokens - 1 && (nPos = strSource.find(strDelimiter)) != -1)
	{
		strValue = strSource.substr(0,nPos); 
		if (strValue.empty())
		{
			if (bReturnEmptyTokens)
				vTokens.push_back(strValue);
		}
		else
			vTokens.push_back(strValue);

		strSource = strSource.substr( nPos + 1, strSource.length()); 
		//strSource.TrimLeft(); strSource.TrimRight();
		
	}
	if (!strSource.empty())
		vTokens.push_back(strSource);
	return vTokens;
}

void run_vector_split()
{
	vector<string> vec_strings = SplitDelimiterLine("main, related,", (","), 3);
	for (auto str : vec_strings)
	{
		cout << str;
	}
}

//int main()
//{
//	run_vector_split();
//	return 0;
//}
