// src/cpp/util/utils.cpp
/*
 * utils.hpp implementation.
 * Utility functions, that are platform independant.
 * 
 * Since: 2019-02-17
 * LastEdit: 2019-02-22
 */

#include <util/utils.hpp>
#include <os.hpp>
#include <stdexcept>

#if OS_is_gnu_linux
#include <libgen.h>
#elif OS_is_win
#include <pathcch.h>
#include <fileapi.h>
#endif

#include <cstring>

namespace game {
	namespace util {

		bool istrue(char* cs) {
			if(cs == NULL || strlen(cs) == 0) return false;

			if(cs[0] == 't' || cs[0] == 'T') return true;

			try {
				int i = std::stoi(cs);
				return i;
			} catch(std::invalid_argument& e) {
				return false;
			}
		}

		char* mbasename(char* path) {
#if OS_is_gnu_linux
			size_t soc = sizeof(char);

			size_t path_size = soc * strlen(path) + soc;
			char* path_cp = (char*)malloc(path_size);
			strcpy(path_cp, path);

			char* dirname_tmp = basename(path_cp);

			size_t size_dirname = soc * strlen(dirname_tmp) + soc;
			char* dirname = (char*)malloc(size_dirname);
			strcpy(dirname, dirname_tmp);

			free(path_cp);
			return dirname;
#elif OS_is_win
			return malloc(1); // TODO rpg-game: utils.cpp: game::util::mbasename(char*): WIN OS version
#endif
		}

		char* mdirname(char* path) {
#if OS_is_gnu_linux
			size_t soc = sizeof(char);

			size_t path_size = soc * strlen(path) + soc;
			char* path_cp = (char*)malloc(path_size);
			strcpy(path_cp, path);

			char* dirname_tmp = dirname(path_cp);

			size_t size_dirname = soc * strlen(dirname_tmp) + soc;
			char* dirname = (char*)malloc(size_dirname);
			strcpy(dirname, dirname_tmp);

			free(path_cp);
			return dirname;
#elif OS_is_win
			wchar_t* path_wcs = cstowcs(path);
			size_t len = wcslen(path_wcs);

			PathCchRemoveFileSpec(path_wcs, len);

			char* abspath = wcstocs(path_wcs);

			free(path_wcs);

			return abspath;
#endif
		}

		char* abspath(char* relpath) {
#if OS_is_gnu_linux
			return realpath(relpath, NULL);
#elif OS_is_win
			size_t buf_size = sizeof(char) * 128 + 1;
			char* abspath = (char*)malloc(buf_size);
			size_t buf_size_temp = GetFullPathNameA(relpath, buf_size, abspath, NULL);

			if(buf_size_temp > buf_size) {
				free(abspath);
				abspath = (char*)malloc(buf_size_temp);
				GetFullPathNameA(relpath, buf_size_temp, abspath, NULL);
			}

			return abspath;
#endif
		}

		char* strmcat(const char* str1, const char* str2) {
			char* str = (char*)malloc(strlen(str1) + strlen(str2) + 1);
			strcpy(str, str1);
			strcat(str, str2);
			return str;
		}

		std::string wcstostr(wchar_t* wcs) {
			std::wstring wstr(wcs);
			return std::string(wstr.begin(), wstr.end());
		}

		wchar_t* cstowcs(char* cs) {
			size_t size = strlen(cs) + 1;
			wchar_t* wcs = (wchar_t*)malloc(sizeof(wchar_t) * size);
			mbstowcs(wcs, cs, size);
			return wcs;
		}

		char* wcstocs(wchar_t* wcs) {
			size_t size = wcslen(wcs) + 1;
			char* cs = (char*)malloc(sizeof(char) * size);
			wcstombs(cs, wcs, size);
			return cs;
		}

		/* ================================================================= */

		std::string operator+(const std::string& str,
				const signed short int& h) {
			return str + std::to_string(h);
		}

		std::string operator+(const std::string& str,
				const signed int& i) {
			return str + std::to_string(i);
		}

		std::string operator+(const std::string& str,
				const signed long int& li) {
			return str + std::to_string(li);
		}

		std::string operator+(const std::string& str,
				const signed long long int& lli) {
			return str + std::to_string(lli);
		}

		std::string operator+(const std::string& str,
				const unsigned short int& hu) {
			return str + std::to_string(hu);
		}

		std::string operator+(const std::string& str,
				const unsigned int& iu) {
			return str + std::to_string(iu);
		}

		std::string operator+(const std::string& str,
				const unsigned long int& lu) {
			return str + std::to_string(lu);
		}

		std::string operator+(const std::string& str,
				const unsigned long long int& llu) {
			return str + std::to_string(llu);
		}

	}
}
