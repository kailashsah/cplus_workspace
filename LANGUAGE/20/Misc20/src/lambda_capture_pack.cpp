#include <iostream>
using namespace std;


// lambda init capture
template <typename... Args>
auto fun_aa(Args&&... args) // by value
{
	return[...args = forward<Args>(args)]() { return (args + ...); };
	//return 1;
}
void run_lambda_returned()
{
	auto a = fun_aa(1, 2, 3)();
	cout << a;

}

template <typename... Args>
auto print_lambda_capture(ostream& out, Args&&... args) // by value
{
	return [...args = forward<Args>(args)]() { ((cout << args), ...); };
	//return 1;
}
void run_cout()
{
	print_lambda_capture(cout, 1, 3)(); // don't call this as print_lambda_capture(cout, 1, 3);

}

template <typename... Args>
auto print_lambda_capture_ref(ostream& out, Args&&... args) // by reference 
{
	//return[& ... args = forward<Args>(args)]() { ((cout << args), ...); };
	return[&args ... ]() { ((cout << forward<Args>(args)), ...); }; // check capture
	//return 1;
}


////////////////////////

//int main()
//{
//		
//	//print_lambda_capture_ref(cout, 1, 3)();
//	// 
//	//run_cout();
//	//run_lambda_returned();
//	return 1; 
//}

////////////////////////

