import <iostream>;

using namespace std;

//1.
auto sum_auto = [](auto a, auto b) {return a + b; };
//2.
auto sum_template = []<typename T>(T a, T b) {return a + b; };
//3.
auto sum_auto_2 = [](auto a, decltype(a) b) {return a + b; }; // valid version
//4.
auto sum_concept = []< integral T >(T a, T b) { return a + b; }; // sum based on concept

void run_lambdas()
{
	//1.
	cout << sum_auto(true , 2) ;		// valid  // 3 // for type check template version req
	
	//2.									
	//cout << sum_template(true, 2 );		// error - 'auto sumTem::<lambda_1>::operator ()(T,T) const': could not deduce template argument for 'T' from 'int'	
 
	//3.
	cout << sum_template(static_cast<int>(true), 2); // valid
	cout << sum_template(6, 2);			// 8 // valid

	//4.
	//cout << sum_concept( true, 2 ); //  c++20 (use of integral)  auto sumConc::<lambda_3>::operator ()(T,T) const': could not deduce template argument for 'T' from 'int'
	
}

//int main()
//{
//	run_lambdas();
//
//	return 1;
//}