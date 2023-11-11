#include <iostream>
using namespace std;


#include <coroutine> 

class resumable {

public:
	struct promise_type;
	using coro_handle = std::coroutine_handle<promise_type>;
	resumable(coro_handle& handle) : _handle(handle) {}
	resumable(const resumable&)= delete;
	resumable(resumable&&) =delete;
	bool resume() {
		if (not _handle.done())
			_handle.resume();
		return not _handle.done();
	}
	~resumable()
	{
		_handle.destroy();
	}

private:
	coro_handle _handle;
};

struct resumable::promise_type
{
public:
	using coro_handle = std::coroutine_handle<promise_type>;
	auto get_return_object() {
		return std::coroutine_handle<promise_type>::from_promise(*this);
	}
	auto initial_suspend() {
		return suspend_always();
	}
	auto final_suspend() noexcept {
		return suspend_always();
	}
	void return_void() {}
	void unhandled_exception() {
		terminate();
	}

private:


};


resumable fun_corountine()
{
	cout << "a" << endl;
	co_await std::suspend_always(); 
	cout << "b" << endl;
	co_await std::suspend_always(); 
	cout << "c" << endl;
}

//int main()
//{
//	resumable res =  fun_corountine();
//	res.resume();
//	res.resume();
//	return 1; // prints - a  b, c-> won't be printed
//}

////////////////////////

