import <iostream>;

using namespace std;

auto sumGen = [](auto a, auto b) {return a + b; };
auto sumTem = []<typename T>(T a, T b) {return a + b; };

//auto sumGen_2 = [](auto a, decltype(a) b) {return a + b; }; // valid version

auto sumConc = []< integral T >(T a, T b) { return a + b; }; // sum based on concept

void run_lambdas()
{
	cout << sumGen(true , 2) ;		// valid  // 3 // for type check template version req
	//cout << sumTem(true, 2 );		// error - 'auto sumTem::<lambda_1>::operator ()(T,T) const': could not deduce template argument for 'T' from 'int'	
 
	cout << sumTem(static_cast<int>(true), 2); // valid

	//cout << sumConc( true, 2 ); //  c++20 (use of integral)  auto sumConc::<lambda_3>::operator ()(T,T) const': could not deduce template argument for 'T' from 'int'

	cout << sumTem(6, 2);			// 8 // valid
}

//int main()
//{
//	run_lambdas();
//
//	return 1;
//}