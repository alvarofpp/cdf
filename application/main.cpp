#include <iostream>
#include <string>

#include "cdf.h"

using namespace std;

int main(int argc, char * argv[])
{
	string fileName = "data/simple.csv";
	cdf::DataFrame cdf = cdf::DataFrame(fileName, ';');
	cdf.debugging();
	cout << cdf[1]["value1"] << endl;
	cout << cdf["value1"][1] << endl;
	cout << endl;

	cdf.drop(1);
	cdf.debugging();
	cout << endl;
	
	cdf.drop("value1");
	cdf.debugging();
	cout << endl;

	cdf.drop("index");
	cdf.debugging();
	cout << endl;

	cdf.drop("value2");
	cdf.debugging();
	cout << endl;

    return EXIT_SUCCESS;
}
