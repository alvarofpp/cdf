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
		private:
			void debugging ();
	};
}

#endif /* __CDF_H__ */