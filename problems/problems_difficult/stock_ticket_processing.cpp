#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <map>
using namespace std;

void stockTicker( string strInput) {

    stringstream ss(strInput);

    map<string, double> stockList;
    string item;
    string stock{};
    double price{};
    while (getline(ss, item, ' ')) {
        stock = item;
        if (stock[0] == ' ')
            continue;
        if (!stock.empty()) {
            getline(ss, item, ' '); // price
            while (item[0] == ' ')
                getline(ss, item, ' '); // price
            if (item.empty())
                continue;
            price = strtod(item.c_str(), NULL);
            auto itr = stockList.find(stock);
            if (itr != stockList.end()) {
                price += itr->second;
                stockList[stock] = price;
            }
            else
                stockList.insert({ stock, price });
        }
    }

    // print stock: price
    for (auto stock : stockList) {
        cout << stock.first << ": " << stock.second << endl;
    }
}

#include <algorithm>
bool isBothSpaces(char lhs, char rhs) {
    return (lhs == rhs) && (lhs == ' ');
}

string removeDupSpaces(string& input) {
    if (0) {
        string::iterator new_end;
        new_end = unique(input.begin(), input.end(), isBothSpaces);
        input.erase(new_end, input.end());
        return input;
    }
    if (1) {
        string::iterator new_end;
        /*new_end = unique(input.begin(), input.end(), [=](char lhs, char rhs) -> bool
            {
                return (lhs == rhs) && (lhs == ' ');
            }
        );*/

        new_end = unique(input.begin(), input.end(), [=](char lhs, char rhs) -> bool
            {
                return (lhs == rhs) && ( isspace(lhs ));
            }
        );

        input.erase(new_end, input.end());
        return input;
    }
    if (1) {

        //transform();

    }
    
}

void run_stock() {
    string strInput;
    //getline(cin, strInput);
    strInput = "AMZ 1.2 GGL +50 IBM  -20";
    strInput = "AMZ                1.2                 GGL +50 IBM  -20";
    //strInput = "AMZ 1.2 GGL +50 IBM  -20";
    //replace(strInput.begin(), strInput.end(), ' ', '_'); // char can't replace a string
    cout << "after removing dup : " << removeDupSpaces(strInput) << endl;
    
    //stoi(); // string to int
    //stod(); // string to double
    // atof(); // string to double
    stockTicker(strInput);
}

//int main() {
//    run_stock();
//}
//



