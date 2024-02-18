#include <iostream>
using namespace std;

/*
    1.  
*/
void run_shared_lock_3();
//
#include <unordered_map>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <string>
#include <iostream>

class PhoneBook {
public:
    string getPhoneNo(const std::string& name)
    {
        shared_lock<shared_timed_mutex> r(_protect); //read lock
        auto it = _phonebook.find(name);
        if (it == _phonebook.end())
            return (*it).second;
        return "";
    }
    void addPhoneNo(const std::string& name, const std::string& phone)
    {
        unique_lock<shared_timed_mutex> w(_protect); //write lock
        _phonebook[name] = phone;
    }

    shared_timed_mutex              _protect;
    unordered_map<string, string>   _phonebook;
};


void run_shared_lock_3() {
}

//int main()
//{
//    run_shared_lock_two();
//}