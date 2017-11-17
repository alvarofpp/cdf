#include "cdf.h"

#include <iostream>  // std::cout, std::endl, std::cin

using namespace std;


/************************************
********* Display functions *********
************************************/

void cdf::DataFrame::head ( size_t _n )
{
	if (dfRows == 0)
	{
		print_alert("Dataframe does not have data to display.");
		return;
	}

	if (_n > dfRows)
		_n = dfRows;
	// Print header
	for (size_t j = 0; j < dfCols; j++)
		cout << dfHeaders[j] << dfDelimiter;
	cout << endl;
	// Print data
	for (size_t i = 0; i < _n; i++)
	{
		for (size_t j = 0; j < dfCols; j++)
			cout << dfData[i][j] << dfDelimiter;
		cout << endl;
	}
}

void cdf::DataFrame::tail ( size_t _n )
{
	if (dfRows == 0)
	{
		print_alert("Dataframe does not have data to display.");
		return;
	}

	if (_n > dfRows)
		_n = dfRows;
	// Print header
	for (size_t j = 0; j < dfCols; j++)
		cout << dfHeaders[j] << dfDelimiter;
	cout << endl;
	// Print data
	for (size_t i = _n; i > 0; i--)
	{
		for (size_t j = 0; j < dfCols; j++)
			cout << dfData[ dfRows-i ][j] << dfDelimiter;
		cout << endl;
	}

}