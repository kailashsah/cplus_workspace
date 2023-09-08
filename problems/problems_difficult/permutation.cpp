#include <iostream>
using namespace std;
// 
/*

*/
#include <vector>
void permute(string str, int start, vector<string>& ans)
{
    if (start == str.size() ) 
    {
        ans.push_back(str);
        return;
    }

    for (int i{start}; i < str.size(); ++i) {

        if (i != start && str[i] == str[start])
            continue;
        
        swap(str[i], str[start]);
        permute(str, start + 1, ans); // recursion
    }
}

void run_permute()
{
    vector<char> vec;
    string str;
    
    int n = 3;
    for (int i{ 1 }; i <= n; ++i) {
        str.push_back('0'+ i);
    }
    cout << "org string :" << str << endl;
    
    vector<string> vec_s;
    permute(str, 0, vec_s);
    for (auto s:vec_s) {
        cout << s << endl;
        /*org string : 123
            123
            132
            213
            231
            312
            321
        */
    }
}

//int main()
//{
//    // ...........................................
//    run_permute();
//    // ...........................................
//}



