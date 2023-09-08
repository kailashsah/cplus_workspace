#include <iostream>

using namespace std;

// for blackberry
void array_oneD(int (&p) [3]) {
	int count = sizeof p / sizeof(int);
	for (int i{}; i < count; ++i) {
		cout << i << " ";
	}
}

void array_twoD(int (&p) [2][3]) {
	cout << endl;
	int r_count = sizeof (p) / sizeof(p[0]);
	int c_count = sizeof(p[0]) / sizeof(int);
	for (int i{}; i < r_count; ++i) {
		for (int j{}; j < c_count; ++j) {
			cout << p[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void array_pointer(int (*p)[2][3]) {
	for (int i{}; i < 2; ++i) {
		for (int j{}; j < 3; ++j) {
			cout << (*p)[i][j] << " ";
		}
		cout << endl;
	}
}

void array_size() {
	int arr_2[][3] = { {1, 2, 3 },
					{1, 8, 3 }
	};
	int r = sizeof(arr_2) / sizeof(arr_2[0]);
	int c = sizeof(arr_2) / sizeof(int);
	//int size = sizeof(int) * 2 * 3;
	int size = sizeof(int) * r * c;

	int arr_dest[2][3] = {0};
	array_twoD(arr_dest);
	cout << "after cpy";
	memcpy(arr_dest, arr_2, size);
	array_twoD(arr_dest);
	cout << endl;
	//
	// access a[1][2]
	int ele = *(&arr_2[0][0] + 1 * r + 2); // 2 col index
	cout << ele;

}

#include <array>
void array_stl() {
	cout <<"array<> stl:"<< endl;
	array<int, 5> arr = {0};
	for (int n : arr) {
		cout << n << " ";
	}
}
#include <vector>
void array_vec(vector<vector<int>>& vec) {
	cout << "array by vector" << endl;
	vector<vector<int>> vec_sample = { {0,0}, {1,1}, {2,2} }; // not used
	int r = vec.size();
	int c = vec[0].size();
	cout << endl;
	for (auto ele : vec) {
		cout << ele[0] << " " << ele[1] << " " ;
		cout << endl;
	}
	
}

void run_array() {
	
	// initialization
	int arr_3 = {0};
	int arr_4[] [3]= { {0}, {0}
					};
	//array_twoD(arr_4);
	
	// 1.
	int arr[] = {1, 2, 3};
	cout << "oneD array " << endl;
	//array_oneD(arr);
	cout << endl;
	
	// 2.
	int arr_2[][3] = { {1, 2, 3 },
					{1, 2, 3 }
	};
	cout << "twoD array " << endl;
	//array_twoD(arr_2);
	cout << endl;
	
	// 3.
	//array_size();

	// 4.
	//array_stl();
	
	// 5. using vector
	vector<vector<int>> vec = { {0,0}, {1}, {2,2} };
	//array_vec(vec);
	
	// 6. array pointer
	array_pointer(&arr_2);

}

//int main() {
//	run_array();
//}


