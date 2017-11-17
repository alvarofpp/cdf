#include "cdf.h"

#include <iostream>  // std::cout, std::endl, std::cin

using namespace std;


/*********************************
********* CRUD functions *********
*********************************/

bool cdf::DataFrame::drop ( size_t _idx )
{
	if (_idx >= dfRows)
	{
		cout << cdf::ALERT_BEGIN << "Invalid row index!" << cdf::ALERT_END << endl;
		return false;
	}

	for (size_t i = _idx; i < dfRows-1; i++)
		dfData[i] = dfData[i+1];

	dfData.resize( --dfRows );

	return true;
}

bool cdf::DataFrame::drop ( string _idx )
{
	int col = find_column(_idx);
	if (col == -1)
	{
		cout << cdf::ALERT_BEGIN << "Invalid column index!" << cdf::ALERT_END << endl;
		return false;
	}
	// Remove data
	for (size_t i = 0; i < dfRows; i++)
	{
		for (size_t j = col; j < dfCols-1; j++)
			dfData[i][j] = dfData[i][j+1];
		
		dfData[i].resize( dfCols-1 );
	}

	// Remove header
	for (size_t j = col; j < dfCols-1; j++)
		dfHeaders[j] = dfHeaders[j+1];
	dfHeaders.resize ( --dfCols );

	// Resize the dimension if columns reaches 0
	if (dfCols == 0)
	{
		dfData.resize(0);
		dfRows = 0;
	}

	return true;
}