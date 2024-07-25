#include <iostream>

using namespace std;

namespace func_hiding {

	class Base {
	public:
		void func(int i) {
			cout << "base" << endl;
		}

	};

	class Derived: public Base {
	public:
		using Base::func;
		void func(char c) {
			cout << c << endl;
			cout << "derived" << endl;
		}
	};

	int main() {
		cout << "func::hiding" << endl;

		Derived d;
		d.func('a');
		d.func(10);

		return 0;

	}
}

/*
int main ()
{
	func_hiding::main();
}
*/
