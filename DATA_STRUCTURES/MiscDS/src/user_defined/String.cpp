#include<iostream>

#define _CRT_SECURE_NO_WARNINGS
using namespace std;

class String
{
private:
	char* m_pBuf = nullptr;

public:
	String() {
		cout << "default ctor called" << endl;

		m_pBuf = new char[1];
		m_pBuf[0] = '\0';
		//m_pBuf = nullptr; 
	}
	String(const char* pbuf) {
		cout << "one param ctor called for -- "<< pbuf << endl;

		long len = strlen(pbuf);
		m_pBuf = new char[len + 1];
		strcpy(m_pBuf, pbuf);

	}
	~String()
	{
		if (m_pBuf)
			cout << "dtor called for --" << m_pBuf << endl;
		else cout << "dtor called for -- null value" << endl;

		if (m_pBuf != nullptr)
			delete[] m_pBuf;
	}
	void print()
	{
		if (m_pBuf)
			cout << m_pBuf << endl;

	}
	friend ostream& operator<< (ostream& os, const String& str)
	{
		os << str.m_pBuf;
		return os;
	}
	friend istream& operator>> (istream& in, String& str)
	{
		cout << "insert optr called" << endl;

		char* buff = new char[1000];
		memset(buff, 0, sizeof(buff));
		in >> *buff;
		cout << "before assignment" << endl;
		str = String{ buff };  // move assignment operator called after ctor
		delete[] buff;
		//in >> *str.m_pBuf;
		//in >> *p;
		return in;
	}
	String& operator=(String& str)
	{
		cout << "assignment called" << endl;
		delete[] this->m_pBuf;
		this->m_pBuf = new char[strlen(str.m_pBuf) + 1];
		strcpy(this->m_pBuf, str.m_pBuf);
		return *this;
	}
	String(String&& str) noexcept
	{
		cout << "move ctor called" << endl;
		
		//delete[] this->m_pBuf; // delete str, temp variable as in call
		this->m_pBuf = new char[strlen(str.m_pBuf) + 1];
		strcpy(this->m_pBuf, str.m_pBuf);
		
		// for arg pointers
		delete[] str.m_pBuf;
		str.m_pBuf = nullptr;

	}
	String& operator =(String&& str)
	{
		cout << "move assignment called" << endl;
		if (this != &str)
		{
			delete[] m_pBuf;
			//this->m_pBuf = new char[strlen(str.m_pBuf) + 1]; // not the proper way
			//strcpy(this->m_pBuf, str.m_pBuf);
			this->m_pBuf = str.m_pBuf;
			
			// for arg pointers
			str.m_pBuf = nullptr;
			//str.~String();
		}
		return *this;
	}
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//I had put the main Function Below this function.
//d for asking string,f is pointer to the string pointer
void GetStr(const char* d, char** f)
{
	printf("%s", d);
	for (int i = 0; 1; i++)
	{
		if (i)//I.e if i!=0
			*f = (char*)realloc((*f), i + 1);
		else
			*f = (char*)malloc(i + 1);
		(*f)[i] = getchar();
		if ((*f)[i] == '\n')
		{
			(*f)[i] = '\0';
			break;
		}
	}
}

void read_string()
{
	cout << endl << "read_string() : " << endl;

	// read indefinite characters from console.
	char* s = NULL;
	GetStr("Enter string : ", &s);
	printf("Your String:- %s \nAnd It's length:- %lu\n", s, (strlen(s)));
	//printf("Your String:- %s \n", *s);
	free(s);
}

void run_stringcpp()
{
	//1.
	read_string();

	//2. move assignment
	cout << endl << "str_src = move(str_two) : " << endl;

	String str_src("one");
	String str_two("two");
	str_src = move(str_two); // move assignment called
	cout << str_src << endl;

	//3. move ctor
	cout << endl << "String str_mv =  std::move(String(\"mv\")) : " << endl;
	String str_mv = std::move(String("mv")); // move ctor
	cout << str_mv << endl;
	/*
		String str_mv =  std::move(String("mv")) :
		one param ctor called for -- mv
		move ctor called
		dtor called for --mv
		mv
	*/

	//4. assignment
	cout << endl << "assignment : " << endl;

	String str("abc");
	String str1 = "saa11111";

	str = str1;
	cout << str << endl;
	cout << str1 << endl;
	
	//5. 
	cout << endl << "insertion optor : " << endl;
	String str_cin; // insertion optor
	cin >> str_cin;
	cout << "after cin  " << str_cin << endl;
	

	cout << "prg stopped" << endl;
}

//int main()
//{
//	run_stringcpp();
//	return 0;
//}