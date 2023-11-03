#include <iostream>
using namespace std;
/*
	1. we cannot set value to future directly, can be done via promise
	2. same future object can be used in multiple async functions. compiles ok
	3. everytime its ptr points to different location of Associated_state<int>. (IMP)
*/

void run_future_valid();
void run_future_get_two_times();
void run_assign_two_futures_in_same();
//
#include <future> // async()

future<int> ft;
//future<int> ft{};
//future<int> ft = future<int>(); // we cannot set value to future directly, can be done via promise

void run_future_valid() {
	async(launch::async, []() {return 100; });
	if (ft.valid())
	{
		int a = ft.get(); //exception: std::future_error // if not used under ft.valid()
		cout << "result: " << a << endl;
	}
}

void run_future_get_two_times() {
	ft = async(launch::async, []() {return 100; });
	if (ft.valid())
	{
		int a = ft.get(); //exception: std::future_error 
		try {
			a = ft.get(); // 2nd get() cause exception // ft state is pending
		}
		catch (const std::future_error& e) {
			//1.
			std::cout << e.code() << e.what() << endl; // "future:4" "no state"		

			//2.
			error_code ec = e.code(); //	<system_error>		
			string smsg = ec.message();
			cout << smsg << endl;

			//3.
			int value = ec.value();
			string smsg_v1 = ec.category().message(value);
			cout << smsg << endl;

			/*
				std::error_code represents a platform-dependent error code value. Each std::error_code object holds an error code value originating from the operating system or some low-level interface and a pointer to an object of type std::error_category, which corresponds to the said interface. The error code values are not required to be unique across different error categories.
			*/
		}
		catch (exception& e) {
			cout << e.what() << endl; // no state
		}
		cout << "result: " << a << endl;
	}

}

void run_assign_two_futures_in_same() {
	// checked seq or parallel in this case
	//1.
	cout << &ft << endl; //001D3270
	cout << ft._Ptr() << endl; // 0000000
	ft = async(launch::async, []() {
		int itr = 1;
		while (itr < 30) {
			//cout << itr; // open to check parallelism.
			itr++;
		}
		cout << endl;
		return 100; });
	cout << &ft << endl; //001D3270
	cout << ft._Ptr() << endl; // 00CB5178

	//2.
	ft = async(launch::async, []() {
		int itr = 1;
		while (itr < 30) {
			//cout << itr;
			itr++;
		}
		cout << endl;
		return 200; });
	cout << &ft << endl; //001D3270
	cout << ft._Ptr() << endl; // 00CB6588

	//3.
	//ft = ft1; // if auto ft1 = async(launch::async ... // operator = deleted function
	if (ft.valid())
	{
		int res = ft.get();
		cout << "result: " << res << endl;
	}
	/*
		conclusion -
			both async threads/functions are parallel.
			ft contains 200, that is, last set value.
	*/
}

//int main() {
//	//run_future_valid();
//	//run_future_get_two_times();
//	run_assign_two_futures_in_same();
//}

