#include <iostream>
#include <string>

#include "cdf.h"

using namespace std;

int main(int argc, char * argv[])
{
	string fileName;
	cin >> fileName;
	cdf::DataFrame cdf = cdf::DataFrame(fileName, ';');
	cout << cdf[0][1] << endl;

    return EXIT_SUCCESS;
}
