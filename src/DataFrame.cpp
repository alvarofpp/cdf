#include "cdf.h"

#include <iostream>  // std::cout, std::endl, std::cin
#include <fstream>   // std::ifstream
#include <algorithm> // std::count, std::for_each
#include <typeinfo>  // debugging

using namespace std;


/*******************************************
********* Constructs and Destructs *********
*******************************************/

cdf::DataFrame::DataFrame ( string _fileName, char _delimiter )
{
	// Open CSV file
	ifstream csvFile(_fileName);
	dfFileName = _fileName;
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
	dfDimension[0] = countDelimiters+1;
	// Save headers
	string header = "";
	dfHeaders.reserve( countDelimiters+1 );
	for (auto i = headersLine.begin(); i < headersLine.end(); i++)
	{
		// EXAMPLE1, EXAMPLE2, example3
		if ((*i) == _delimiter)
		{
			dfHeaders.push_back(header);
			header = "";
		}
		// example1, example2, EXAMPLE3
		else if (i == headersLine.end()-1)
		{
			header += (*i);
			dfHeaders.push_back(header);
			header = "";
		}
		else
			header += (*i);
	}

	// Start the saving data
	size_t dfDimensionY = 0;
	// References
	string &fileLine = headersLine;
	string &line = header;
	// Alias of size_t
	std::string::size_type sz;
	double value;

	while ( getline(csvFile, fileLine) )
	{
		dfData.resize( ++dfDimensionY );
		dfData[ dfDimensionY-1 ].reserve( dfDimension[0] );

		for (auto i = fileLine.begin(); i < fileLine.end(); i++)
		{
			// EXAMPLE1, EXAMPLE2, example3
			if ((*i) == _delimiter)
			{
				value = std::stod(line, &sz);
				dfData[ dfDimensionY-1 ].push_back( value );
				line = "";
			}
			// example1, example2, EXAMPLE3
			else if (i == headersLine.end()-1)
			{
				line += (*i);
				value = std::stod(line, &sz);
				dfData[ dfDimensionY-1 ].push_back( value );
				line = "";
			}
			else
				line += (*i);
		}
	}
	// Save dimension Y
	dfDimension[1] = dfDimensionY;
}


/***************************
********* Operator *********
***************************/

cdf::DataFrame::DataFrameVector cdf::DataFrame::operator[] ( size_t _idx )
{
	return DataFrameVector( *this, _idx, DataFrameVector::LINE );
}

cdf::DataFrame::DataFrameVector cdf::DataFrame::operator[] ( string _idx )
{
	return DataFrameVector( *this, _idx, DataFrameVector::COLUMN );
}


/****************************
********* Functions *********
****************************/

bool cdf::DataFrame::drop ( size_t _idx )
{
	if (_idx >= dfDimension[1])
	{
		cout << cdf::ALERT_BEGIN << "Invalid row index!" << cdf::ALERT_END << endl;
		return false;
	}

	for (size_t i = _idx; i < dfDimension[1]-1; i++)
		dfData[i] = dfData[i+1];

	dfData.resize( --dfDimension[1] );

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
	for (size_t i = 0; i < dfDimension[1]; i++)
	{
		for (size_t j = col; j < dfDimension[0]-1; j++)
			dfData[i][j] = dfData[i][j+1];
		
		dfData[i].resize( dfDimension[0]-1 );
	}

	// Remove header
	for (size_t j = col; j < dfDimension[0]-1; j++)
		dfHeaders[j] = dfHeaders[j+1];
	dfHeaders.resize ( --dfDimension[0] );

	// Resize the dimension if X reaches 0
	if (dfDimension[0] == 0)
	{
		dfData.resize(0);
		dfDimension[1] = 0;
	}

	return true;
}


/*************************
********* Friend *********
*************************/

ostream & cdf::operator<< ( ostream & _out, const DataFrame & _df )
{
	// Filename XxY
	_out << _df.dfFileName << " " << _df.dfDimension[0] << "x" << _df.dfDimension[1] << endl;
	// Headers
	_out << ".Headers: ";
	for (size_t i = 0; i < _df.dfHeaders.size(); i++)
		_out << _df.dfHeaders[i] << ";";
	_out << endl << ".Data: " << endl;
	// Data
	for (size_t i = 0; i < _df.dfDimension[1]; i++)
	{
		for (size_t j = 0; j < _df.dfDimension[0]; j++)
			_out << _df.dfData[i][j] << ";";
		_out << endl;
	}

    return _out;
}

/**************************
********* Private *********
**************************/

int cdf::DataFrame::find_column ( string _column )
{
	for (size_t i = 0; i < dfDimension[0]; i++)
	{
		if (_column == dfHeaders[i])
			return i;
	}

	return -1;
}