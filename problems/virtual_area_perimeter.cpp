#include <iostream>

using namespace std;

namespace area {
	class B {
	public:
		int A;
		int B1;

		virtual void init(int a, int b) {
			A = a;
			B1 = b;
		}
		virtual  void area() {
			cout << "In base\n";

		}
		virtual  void perimeter() {
			cout << "In base\n";

		}
	};


	// Complete the classes

	class D1 :public B {

		void area()
		{
			cout << A*B1;
		}
	};//D1 contains the member functions init and area

	class D2 :public B {

		void perimeter()
		{
			cout << 2 * (A + B1);
		}
	};//D2 contains the memeber function init and perimeter


	int main() {
		B *b;
		D1 d1;
		D2 d2;

		int A, B;
		cin >> A >> B;
		b = &d1;
		b->init(A, B);
		cout << "area: ";
		b->area();
		b = &d2;
		cout << "\n";
		b->init(A, B);
		cout << "perimeter: ";
		b->perimeter();
		return 0;
	}

}