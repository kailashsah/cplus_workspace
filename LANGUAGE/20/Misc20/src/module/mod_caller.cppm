
//#include <iostream>
import <iostream>;
using namespace std;


import AdvancedMathematicsModule;   // module imported

void run_module() {
	//1.
	cout << " minus :" << AdvancedMathematicsNamespace::minus(6, 2) << endl; // 4
	cout << " plus : " << plus_int(6, 2) << endl; // 8

	//2.
	//cout << " minus :" << minus(6, 2) << endl; // compilation error, needs namespace
	//3.
	//this_function_will_not_be_exported(); // error C3861: 'this_function_will_not_be_exported': identifier not found

}

//int main()
//{
//	run_module();
//	return 1;
//}



/*
	1. A module is made up of one or more source code files compiled into a binary file. The binary file describes all the exported types, functions, and templates in the module. When a source file imports a module, the compiler reads in the binary file that contains the contents of the module. Reading the binary file is much faster than processing a header file. Also, the binary file is reused by the compiler every time the module is imported, saving even more time. Because a module is built once rather than every time it's imported, build time can be reduced, sometimes dramatically.

	2. More importantly, modules don't have the fragility problems that header files do. Importing a module doesn't change the module's semantics, or the semantics of any other imported module. Macros, preprocessor directives, and non-exported names declared in a module aren't visible to the source file that imports it. You can import modules in any order and it won't change the meaning of the modules.

	3. .ixx  - module extension
		cppm - Implement module file, normal src file using "import" rather than #include

	4. import<iostream>; - In terms of compiling speed when multiple modules are called from different parts of the code, import statement seems to be quicker than the old #include preprocesor directive.

	5.
	Module interface units can export declarations (including definitions), which can be imported by other translation units

	6.
	What is the difference between import and include?
	include is used for including the content of a file into your current program. It has nothing to do with modules or namespaces. 
	
	using import on the other hand have nothing to do with files, and deal exclusively with modules/namespaces.

*/
