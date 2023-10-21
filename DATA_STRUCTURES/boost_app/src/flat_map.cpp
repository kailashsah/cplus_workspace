// boost_app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <boost/container/flat_map.hpp>

void run_flat_map() {
    boost::container::flat_map<int, std::string> mymap{ {1, "one"}, {2, "two"}, {3, "three"} };

    for (auto [k, v] : mymap) {
        std::cout << k << ": " << v << '\n';
    }

    /*
        1: one
        2: two
        3: three
    */
}


int main()
{
	run_flat_map();
	return 0;
}
