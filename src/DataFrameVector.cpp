#include "cdf.h"

using namespace std;


/***************************
********* Operator *********
***************************/

cdf::DataFrame::reference cdf::DataFrame::DataFrameVector::operator[] ( int _idx )
{
    return dfParent.dfData[idx][_idx];
}

cdf::DataFrame::reference cdf::DataFrame::DataFrameVector::operator[] ( string _idx )
{
	int col = dfParent.find_column( _idx );
    return dfParent.dfData[idx][col];
}