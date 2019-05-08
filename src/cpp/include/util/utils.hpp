// src/cpp/include/util/utils.hpp
/*
 * Utility functions, that are platform independant.
 * 
 * Since: 2019-02-17
 * LastEdit: 2019-02-22
 */

#ifndef HE56D4095_0213_41E1_9458_4DFBEB900819
#define HE56D4095_0213_41E1_9458_4DFBEB900819

#include <string>

namespace game {
	namespace util {

		bool istrue(char* cs);
		char* mbasename(char* path); // malloc basename
		char* mdirname(char* path); // malloc dirname
		char* abspath(char* relpath); // absolute path (using malloc)
		char* strmcat(const char* str1, const char* str2); // string malloc concat
		std::string wcstostr(wchar_t* wcs); // wide c-string to std::string
		wchar_t* cstowcs(char* cs); // c-string to wide c-string (using malloc)
		char* wcstocs(wchar_t* wcs); // wide c-string to c-string (using malloc)

		std::string operator+(const std::string& str,
				const signed short int& h);
		std::string operator+(const std::string& str,
				const signed int& i);
		std::string operator+(const std::string& str,
				const signed long int& li);
		std::string operator+(const std::string& str,
				const signed long long int& lli);
		std::string operator+(const std::string& str,
				const unsigned short int& hu);
		std::string operator+(const std::string& str,
				const unsigned int& iu);
		std::string operator+(const std::string& str,
				const unsigned long int& lu);
		std::string operator+(const std::string& str,
				const unsigned long long int& llu);

	}
}

#endif
