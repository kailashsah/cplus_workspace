#include <iostream>
//#include "../cplus20/cplus20.h"
using namespace std;

#define cplus20
#ifdef cplus20

/* 
	1. Implementing Lazy generators with Coroutines
	2. https://www.youtube.com/watch?v=TgAFja228HU
	3. The C++ coroutines are a control structure in which the control flow is passed along with the different routines without returning.
		The C++ coroutine is a function that can prevent the execution that needs to be resumed later.

	3. The C++ coroutines are of stackless behavior which is why this function returns the result to the caller and continues the specified coroutine that's again stored within the isolated area or stack that's as of now defined.

	4. https://www.scaler.com/topics/cpp-coroutines/ - for understanding
*/
#include <coroutine> 
template<typename T>
class generator {
public:
	struct promise_type;
	using coro_handle = coroutine_handle<promise_type>;
	generator(coro_handle handle) : _handle(handle) {}
	~generator() {  _handle.destroy(); } 
	T get_value() {
		return _handle.promise().current_value;
	}
	bool next() {
		_handle.resume();
		return not _handle.done();
	}
private:
	coro_handle _handle;
};

template<typename T>
struct generator<T>::promise_type {
public:
	//using coro_handle = coroutine_handle<promise_type>;
	auto get_return_object() {

		return coroutine_handle<promise_type>::from_promise(*this);

	}
	auto initial_suspend() {
		return std::suspend_always();
	}
	auto final_suspend()noexcept {
		return suspend_always();
	}
	void return_void(){}
	
	auto yield_value(T value) {
		current_value = value;
		return suspend_always();
	}

	void unhandled_exception() {
		terminate();
	}

//private:
	T current_value;
};

generator<int> getInt(int start = 0, int step =1)
{
	auto value = start;
	for (int i = 0;; ++i)
	{
		co_yield value;  // co_yield is operator 
		// the co_yield expression — to suspend execution returning a value

		value += step;

	}
}
void run_coro_generator()
{
	auto gen = getInt();
	for (int i = 0; i < 10; i++) {
		
		gen.next();

		cout << gen.get_value() << endl; // 0 1 2 ...
	}
	
}

//int main()
//{
//	
//	run_coro_generator();
//	return 1;
//}

#endif

