#include <iostream>
using namespace std;

/*
	1. unscoped enum and scoped enum

	2. Enumeration, or enum for short, is a type whose values are user-defined named constants called enumerators.

	3. These unscoped enums have their enumerators leak into an outside scope, the scope in which the enum type itself is defined.

	3. Scoped enums do not leak their enumerators into an outer scope and are not implicitly convertible to other types.
		scoped enums provide strong type-safety despite being primitive integer types.

	4. https://www.nextptr.com/tutorial/ta1423015134/scoped-class-enums-fundamentals-and-examples 
*/

enum UnscopedEnum
{
	firstvalue, //0
	secondvalue,//1
	thirdvalue	//2	
};
void run_uncoped_enum()
{
	UnscopedEnum myenum = firstvalue;
	//1.
	//UnscopedEnum myenum = UnscopedEnum::firstvalue; // thats also possible
	myenum = secondvalue; // we can change the value of our enum object
	cout << myenum << endl; //1
	
	//2. fyi
	//myenum = 1; //Error	C2440	'=': cannot convert from 'int' to 'UnscopedEnum'

	
	//3. fyi
	/*
		if firstvalue =10
		then secondvalue will be	11
		then thirdvalue will be		12
	*/

	/*cout << firstvalue << endl;
	cout << secondvalue << endl;
	cout << thirdvalue << endl;
	*/
}

//.................................... scoped enum
enum class MyEnum
{
	myfirstvalue,
	mysecondvalue,
	mythirdvalue
};


void run_scoped_enum()
{
	MyEnum myenum = MyEnum::myfirstvalue;
	
	//1.
	//cout << MyEnum::myfirstvalue;		//Error	C2679	binary '<<': no operator found which takes a right - hand operand of type 'MyEnum' (or there is no acceptable conversion)	
	
	cout << static_cast<int>(myenum) << endl; //0
	
}

//int main()
//{
//	//run_uncoped_enum();
//	run_scoped_enum();
//	return 0;	
//}
