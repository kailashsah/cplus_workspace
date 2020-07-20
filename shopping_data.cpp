#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <map>
#include <iomanip>
#include <algorithm>
#include <set>

using namespace std;

struct my_tokenizer_func {
	template<typename It>
	bool operator()(It &next, It end, std::string &tok) {
		if (next == end)
			return false;
		char const *del = ">=";
		auto pos = std::search(next, end, del, del + 2);
		tok.assign(next, pos);
		next = pos;
		if (next != end)
			std::advance(next, 2);
		return true;
	}

	void reset() {
	}
};
class product {
public:
	string id;
	string name; // shoe, mobile
	int quantity = 0;
	string brand; // air, mi
	string location;
public:
	product() = default;

	bool operator==(const product &other) const {
		return (id == other.id);
	}

	product& operator =(const product *other) {
		id = other->id;
		return *this;
	}

};
/*product::product() {
 id = "";
 name = "";
 quantity = 0;
 brand = "";
 location = "";
 }*/

void generateFiles(string input_file_name) {

	//	cout << input_file_name<< endl;

	unordered_multimap<string, product*> orders;
	set<string> product_category;

	string line;
	ifstream inputfile(input_file_name);
	while (std::getline(inputfile, line)) {
		//cout << line << endl;
		stringstream linestream;
		linestream.str(line);

		string token;
		product *item = new product();
		int ctr = 0;
		while (std::getline(linestream, token, ',')) {

			switch (ctr) {
			case 0:
				item->id = token;
				break;
			case 1:
				item->location = token;
				break;
			case 2:
				item->name = token;
				break;
			case 3:
				item->quantity = stoi(token);
				break;
			case 4:
				item->brand = token;
				break;
			}
			ctr++;

		}
		product_category.insert(item->name);
		orders.insert( { item->name, item });
		//orders[item->name] = item;

	}

	product *var = NULL;
	int orders_size = orders.size();
	map<float, pair<string, string>> highest_orders; // get the highest average order

	for (auto product_name : product_category) {
		int order_sum = 0;
		int max = 0;
		string max_brand;
		auto found = orders.equal_range(product_name);

		for (auto it = found.first; it != found.second; it++) {
			var = it->second;
			order_sum += var->quantity;
			if(max < var->quantity)
			{
				max = var->quantity;
				max_brand = var->brand;
			}
			//cout << var->id << setw(4) << var->brand << endl;
		}

		float avg = order_sum/orders_size;
		highest_orders[avg] = make_pair(product_name,max_brand);

	}


	// create output files
	string strFileAverage, strFilePopular;
	strFileAverage = "0" + input_file_name;
	strFilePopular = "1" + input_file_name;

	ofstream fileAverage(strFileAverage);
	for(auto item : highest_orders)
	{
		string write = item.second.first + "," + to_string(item.first);
		fileAverage<<write << endl;
	}

	fileAverage.close();

	ofstream filePopular(strFilePopular);
	for(auto item : highest_orders.rbegin())
		{

		string write = item.second.first + "," + item.second.second;
		filePopular<<write << endl;
		}
	filePopular.close();

}

int main() {

	string input_file_name = "input.csv";
	//getline(cin, input_file_name);

	generateFiles(input_file_name);

	return 0;
}

