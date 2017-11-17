#include "cdf.h"

#include <iostream>  // std::cout, std::endl, std::cin
#include <fstream>   // std::ifstream
#include <algorithm> // std::count

using namespace std;


/*******************************************
********* Constructs and Destructs *********
*******************************************/

cdf::DataFrame::DataFrame ( string _fileName, char _delimiter )
{
	// Open CSV file
	ifstream csvFile(_fileName);
	dfFileName = _fileName;
	dfDelimiter = _delimiter;
	// Check whether state of stream is not good
	if (!csvFile.good())
	{
		print_alert("Filename is invalid!");
		return;
	}
	// Find out number of fields per line
	string headersLine;
	getline(csvFile, headersLine);
	int countDelimiters = count(headersLine.begin(), headersLine.end(), _delimiter);
	dfCols = countDelimiters+1;
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
	size_t rows = 0;
	// References
	string &fileLine = headersLine;
	string &line = header;
	// Alias of size_t
	std::string::size_type sz;
	double value;

	while ( getline(csvFile, fileLine) )
	{
		dfData.resize( ++rows );
		dfData[ rows-1 ].reserve( dfCols );

		for (auto i = fileLine.begin(); i < fileLine.end(); i++)
		{
			// EXAMPLE1, EXAMPLE2, example3
			if ((*i) == _delimiter)
			{
				value = std::stod(line, &sz);
				dfData[ rows-1 ].push_back( value );
				line = "";
			}
			// example1, example2, EXAMPLE3
			else if (i == headersLine.end()-1)
			{
				line += (*i);
				value = std::stod(line, &sz);
				dfData[ rows-1 ].push_back( value );
				line = "";
			}
			else
				line += (*i);
		}
	}
	// Save rows numbers
	dfRows = rows;
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


/*************************
********* Friend *********
*************************/

ostream & cdf::operator<< ( ostream & _out, const DataFrame & _df )
{
	// Filename XxY
	_out << _df.dfFileName << " " << _df.dfRows << "x" << _df.dfCols << endl;
	// Headers
	_out << ".Headers: ";
	for (size_t i = 0; i < _df.dfHeaders.size(); i++)
		_out << _df.dfHeaders[i] << _df.dfDelimiter;
	_out << endl << ".Data: " << endl;
	// Data
	for (size_t i = 0; i < _df.dfRows; i++)
	{
		for (size_t j = 0; j < _df.dfCols; j++)
			_out << _df.dfData[i][j] << _df.dfDelimiter;
		_out << endl;
	}

    return _out;
}


/**************************
********* Private *********
**************************/

int cdf::DataFrame::find_column ( string _column )
{
	for (size_t i = 0; i < dfCols; i++)
	{
		if (_column == dfHeaders[i])
			return i;
	}

	return -1;
}

void cdf::DataFrame::print_alert ( string _msg )
{
	cout << cdf::ALERT_BEGIN << _msg << cdf::ALERT_END << endl;
}