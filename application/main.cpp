#include <iostream>
#include <string>

#include "cdf.h"

using namespace std;

int main(int argc, char * argv[])
{
	string fileName;
	cin >> fileName;
	cdf::DataFrame cdf = cdf::DataFrame(fileName, ';');

    return EXIT_SUCCESS;
}
