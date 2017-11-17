#include <iostream>
#include <string>
#include <vector>

#include "cdf.h"

using namespace std;

int main( int argc, char * argv[] )
{
	string fileName = "data/simple.csv";
	cdf::DataFrame cdf = cdf::DataFrame(fileName, ';');
	cout << cdf << endl;
	cdf.tail(2);

    return EXIT_SUCCESS;
}