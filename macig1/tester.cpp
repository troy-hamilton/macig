#include <iostream>
using namespace std;

// takes pints, cups, ounces
// outputs in ounces
// a pint is two cups, a cup is 8 ounces

int main()
{
	using std::string;
	using std::cout;
	using std::endl;
	
	string outer = "0123456789ABCDEF";
	string inner = "23d";
	size_t indx = outer.find(inner);
	
	cout << indx << endl;
	
}