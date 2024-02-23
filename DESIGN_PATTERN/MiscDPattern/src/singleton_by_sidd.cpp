#include <iostream>
using namespace std;
/*
	1. https://siddswork.com/singleton-design-pattern-in-cpp/
*/
class Resource {
public:
	Resource() { std::cout << "Resource Created\n"; }
	~Resource() { std::cout << "Resource Destroyed\n"; }
	void use() { std::cout << "Resource being used\n"; }
};

class SingletonRes : public Resource {
public:
	~SingletonRes() { std::cout << "SingletonRes destroyed\n"; };
	SingletonRes(const SingletonRes&) = delete;
	SingletonRes& operator=(const SingletonRes&) = delete;

	//1.
	static SingletonRes& getInstance() {
		static SingletonRes resource{};
		return resource;
	}

	//2.
	//static SingletonRes& getInstance() {
	//    static SingletonRes* resource = new SingletonRes();
	//    return *resource;
	//}
private:
	SingletonRes() { std::cout << "SingletonRes created\n"; }
};

/*
	//1.
	>> Program start
	Singleton created
	Singleton being used
	Resource Created
	SingletonRes created
	Resource being used
	<< Program end:
	SingletonRes destroyed  <-- these two are missing in 2nd.
	Resource Destroyed      <--
	Resource being used
	Singleton destroyed

	//2.
	>> Program start
	Singleton created
	Singleton being used
	Resource Created
	SingletonRes created
	Resource being used
	<< Program end:
	Resource being used
	Singleton destroyed
*/

class Singleton {
public:
	~Singleton() {
		SingletonRes::getInstance().use();
		std::cout << "Singleton destroyed\n";
	};
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	void use() { std::cout << "Singleton being used\n"; }

	static Singleton& getInstance() {
		static Singleton resource{};
		return resource;
	}

private:
	Singleton() { std::cout << "Singleton created\n"; }
};

void run_singleton() {
	Singleton::getInstance().use();
	SingletonRes::getInstance().use();
}

//int main() {
//	std::cout << ">> Program start\n";
//
//	run_singleton();
//	std::cout << "<< Program end:\n";
//}