#include <iostream>
using namespace std;

/*
	1. unscoped enum issues

	
*/

//.................................... Case 1
// leaking outside scope
// 
//Side of order 
enum OrderSide { BUY = 1, SELL = -1 };

//A trading signal enumeration from tech. analysis 
enum TradeSignal { Buy, Sell };

void sendMarketOrder(const std::string& ticker, uint32_t size, OrderSide side) {
	//'side' and 'Buy' are promoted for comparison
	if (side == Buy) { //Oops! Compares to TradeSignal::Buy 
		//....
	}
	//.....
}
//.................................... Case 2

//Enumerator names defined in an unscoped enum leak into the enclosing scope. This can lead to name clashes. F
enum Day { Sun, Mon, Tue, Wed, Thu, Fri, Sat }; //All identifiers injected into Day's parent scope

//enum Star { Sun, Sirius, Pollux }; //Error!  ('Sun' already defined in parent scope)


//.................................... Case 3
// assignment and comparisions
enum class AccountType { Checking, Savings };

void spam() {
	//1.
	//AccountType at0 = 0; //Error!
	//int at1 = AccountType::Checking; //Error!
	
	//2.
	AccountType at2 = AccountType::Checking; //OK
	auto at3 = AccountType::Checking; //OK


	if (at2 == at3) { //OK
	}

	//if (at2 == 0) { } //Error! Cannot compare with int
	
}
void spam_fix()
{
	// In those situations where it is necessary, we can explicitly type-cast scoped enums to and from integers:
	AccountType at0 = static_cast<AccountType>(0); //OK
	int at1 = static_cast<int>(AccountType::Checking); //OK
}


//.................................... Case 4
// the enumerator names are defined only within the enum internal scope and implicitly convert to underlying types.We can specify the underlying type for scoped enum :

enum class MyCharEnum : char  // <-- we used underlying type as char
{
	myfirstvalue ,	//0
	mysecondvalue,	//1
	mythirdvalue	//2
};
/*
	char c = static_cast<char>(MyCharEnum::mythirdvalue);

	if myfirstvalue = 'A'
	then mysecondvalue will be B *
	mythirdvalue  will be C
*/

//.................................... Case 5
//1.
//As the size of an unscoped enum without a specific underlying type depends on its enumerators, there is no way to forward - declare them :

//forward-declaration
enum AB; //Error

//2.
//However, it is fine to forward - declare a scoped enum or an unscoped enum with a specified underlying type :

//forward-declaration
enum Asset : uint8_t; //OK 
enum class Shape : uint8_t; //OK

//.................................... main fn
//int main()
//{
//	
//	return 0;	
//}
