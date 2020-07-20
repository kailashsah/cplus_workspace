#include <iostream>
#include <exception>
#include <cstdio>
using namespace std;

namespace norton {
	void MyMethod(int &nParam) {

		nParam++;

	}

	int main() {

		int *pObj = 0;
		int &nObj = *pObj;
		MyMethod(nObj); // this is null reference which is not possible in c++
		//

		printf("%d", nObj);
		cout << nObj;

		getchar();

	}

/*int main() {
	norton::main();
}*/
}


