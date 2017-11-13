#ifndef __CDF_H__
#define __CDF_H__

#include <string>   // std::string
#include <vector>   // std::vector

using namespace std;

namespace cdf
{
	// Color of alerts
	static string ALERT_BEGIN = "\033[1;31m";
	static string ALERT_END = "\033[0m";

	class DataFrame
	{
		public:
			/*
			* Typedef
			*/
			typedef double type;
			typedef double & reference;
			typedef double * iterator;

			class DataFrameVector
			{
				friend class DataFrame;
				enum DFRType
				{
					COLUMN = 0,
					LINE
				};

				private:
					DataFrame& dfParent; // Parent DataFrame
	        		size_t idx;          // Index, can be reference a row or column
	        		int dtType;          // Vector type, helping identify if it is row or column

	        	public:
	        		/*
					* Constructs and Destructs
					*/
					DataFrameVector ( DataFrame & _dfParent, size_t _idx, int _dtType )
					: dfParent( _dfParent ), idx( _idx ), dtType( _dtType ) {}
					~DataFrameVector () = default;
					/*
					* Operator
					*/
	        		reference operator[] ( int _idx );
	        		reference operator[] ( string _idx );

			};

		private:
			string dfFileName;                  // Filename
			size_t dfDimension[2];              // Dimensions X and Y
			vector< string > dfHeaders;         // CSV File headers
			vector< vector< double > > dfData;  // CSV File data

		public:
			/*
			* Constructs and Destructs
			*/
			DataFrame ( string _fileName, char _delimiter = ',' );
			~DataFrame () = default;
			/*
			* Operator
			*/
			DataFrameVector operator[] ( size_t _idx );
			DataFrameVector operator[] ( string _idx );
		private:
			void debugging ();
	};
}

#endif /* __CDF_H__ */