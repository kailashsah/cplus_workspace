#include <iostream>
using namespace std;

/*
	lazy initialization saves resources, as it generate the method only when it is required by the program
*/
template <typename T, std::size_t N>
class Array2 {
public:
	std::size_t getSize() const {
		return N;
	}
private:
	T elem[N];
};


void run_lazy_initialization()
{
	Array2<int, 5> myArr1;
	Array2<double, 5> myArr2;   // (1) 
	myArr2.getSize();           // (2) 
	/*
		 The member function getSize() of the class template Array2 is only instantiated for myArr2 (1). The call causes this instantiation myArr2.getSize() (2).
	*/
}

//int main()
//{
//	run_lazy_initialization();
//	return 0;	
//}

/*
	translated class
	//1.
	template<>
	class Array2<int, 5>
	{

	  public:
	  inline std::size_t getSize() const;


	  private:
	  int elem[5];
	  public:
	  // inline constexpr Array2() noexcept = default;
	};

	//2.
	template<>
	class Array2<double, 5>
	{

	  public:
	  inline std::size_t getSize() const
	  {
		return 5UL;
	  }


	  private:
	  double elem[5];
	  public:
	  // inline constexpr Array2() noexcept = default;
	};
*/