#include "cdf.h"

#include <iostream>  // std::cout, std::endl, std::cin
#include <fstream>   // std::ifstream
#include <algorithm> // std::count

using namespace std;

cdf::DataFrame::DataFrame ( string _fileName, char _delimiter )
{
	// Open CSV file
	ifstream csvFile(_fileName);
	// Check whether state of stream is not good
	if (!csvFile.good())
	{
		cout << cdf::ALERT_BEGIN << "Filename is invalid!" << cdf::ALERT_END << endl;
		return;
	}
	// Find out number of fields per line
	string headersLine;
	getline(csvFile, headersLine);
	int countDelimiters = count(headersLine.begin(), headersLine.end(), _delimiter);
	// Save headers
	string header = "";
	headers.reserve( countDelimiters+1 );
	for (auto i = headersLine.begin(); i < headersLine.end(); i++)
	{
		// EXAMPLE1, EXAMPLE2, example3
		if ((*i) == _delimiter)
		{
			headers.push_back(header);
			header = "";
		}
		// example1, example2, EXAMPLE3
		else if (i == headersLine.end()-1)
		{
			header += (*i);
			headers.push_back(header);
			header = "";
		}
		else
			header += (*i);
	}
	// Debugging
	for (size_t i = 0; i < headers.size(); i++)
		cout << "i: " << i << " = " << headers[i] << endl;
}