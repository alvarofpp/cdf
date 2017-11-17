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
				enum DFVType
				{
					COLUMN = 0,
					LINE
				};

				private:
					DataFrame & dfParent; // Parent DataFrame
					size_t idx;           // Index, can be reference a row or column
					DFVType dtType;       // Vector type, helping identify if it is row or column

				public:
					/*
					* Constructs and Destructs
					*/
					DataFrameVector ( DataFrame & _dfParent, size_t _idx, DFVType _dtType )
					: dfParent( _dfParent ), idx( _idx ), dtType( _dtType ) {}
					DataFrameVector ( DataFrame & _dfParent, string _idx, DFVType _dtType )
					: dfParent( _dfParent ), dtType( _dtType ) { idx = dfParent.find_column( _idx ); }
					~DataFrameVector () = default;
					/*
					* Operator
					*/
					reference operator[] ( int _idx );
					reference operator[] ( string _idx );


				friend class DataFrame;
			};

		private:
			char dfDelimiter;                   // Delimiter
			string dfFileName;                  // Filename
			size_t dfRows, dfCols;              // Rows and columns
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
			/*
			* CRUD functions
			*/
			bool drop ( size_t _idx );
			bool drop ( string _idx );
			/*
			* Display functions
			*/
			void head ( size_t _n = 5 );
			void tail ( size_t _n = 5 );
			/*
			* Friend
			*/
    		friend ostream & operator<< ( ostream &, const DataFrame & );
    		
		private:
			void print_alert ( string _msg );
			int find_column ( string _column );
	};

ostream & operator<< ( ostream & _out, const DataFrame & _df );

}

#endif /* __CDF_H__ */