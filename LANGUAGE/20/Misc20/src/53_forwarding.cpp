#include <iostream>
using namespace std;

/*
	1. perfect forwarding
	2. What is meant by perfect forwarding?

		“Forwarding” is the process where one function forwards its parameter to another function. When it is perfect, the function should receive the same object passed from the function that does the forwarding.

		In other words, perfect forwarding means we do not just forward objects, we also forward their salient properties, whether they are lvalues or rvalues, const or volatile.

	3. https://levelup.gitconnected.com/perfect-forwarding-647e1caaf879
*/

class Object {
public:
	Object() = default;

	void SetName(const std::string& name) { name_ = std::move(name); }
	std::string GetName() const { return name_; }

private:
	std::string name_;
};

// ------------------------------------- functions using Object class
void UseObject(Object&) {
	std::cout << "calling UseObject(Object &)" << std::endl;
}

void UseObject(const Object&) {
	std::cout << "calling UseObject(const Object &)" << std::endl;
}

void UseObject(Object&&) {
	std::cout << "calling UseObject(Object &&)" << std::endl;
}

// ------------------------------------- mediator function to route the call to correct function

//1.
template <typename T>
void HalfForwardToUseObject(T&& x) {  // universal reference
	UseObject(x);
}

void run_half_forwarding_ggg() {
	Object object;
	const Object const_object;
	HalfForwardToUseObject(object);
	HalfForwardToUseObject(const_object);
	HalfForwardToUseObject(std::move(object));
	/*
		calling UseObject(Object&)
		calling UseObject(const Object&)
		calling UseObject(Object&)
	*/
}

//2.
template <typename T>
void ForwardToUseObject(T&& x) {
	UseObject(static_cast<T&&>(x)); // (IMP)
}

void run_perfect_forwarding_ggg() {
	Object object;
	const Object const_object;
	ForwardToUseObject(object);
	ForwardToUseObject(const_object);
	ForwardToUseObject(std::move(object));
	/*
		calling UseObject(Object &)
		calling UseObject(const Object &)
		calling UseObject(Object &&)
	*/
}
int main() {

	//run_half_forwarding_ggg();
	run_perfect_forwarding_ggg();
}