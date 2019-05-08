// src/cpp/include/logger.hpp
/*
 * Header file for the logger object.
 * 
 * Since: 2019-02-17
 * LastEdit: 2019-02-21
 */

#ifndef H43F1EE68_572A_49D4_B830_EBABF58B2440
#define H43F1EE68_572A_49D4_B830_EBABF58B2440

#include <os.hpp>
#include <iostream>

namespace game {
	namespace util {
		inline namespace log {

			using std::ostream;

			class logger {

				public:
				ostream& stream;
				bool esc_sqn_on;

				public:
				logger(ostream& stream, bool enable_esc_sqn = true);

				/* ============================================================= */

				const ostream& get_stream();
				const ostream& operator*();

				bool esc_sqn_enabled();

				/* ============================================================= */

				logger& operator<<(std::string str);
				logger& operator<<(bool b);
				logger& operator<<(signed short int h);
				logger& operator<<(signed int i);
				logger& operator<<(signed long int l);
				logger& operator<<(signed long long int ll);
				logger& operator<<(unsigned short int hu);
				logger& operator<<(unsigned int u);
				logger& operator<<(unsigned long int lu);
				logger& operator<<(unsigned long long int llu);
				logger& operator<<(float f);
				logger& operator<<(double f);
				logger& operator<<(long double lf);
				logger& operator<<(signed char c);
				logger& operator<<(unsigned char uc);
				logger& operator<<(const char* s);
				logger& operator<<(const void* p);
				logger& operator<<(ostream& (*mnp)(ostream&));
				logger& operator<<(logger& (*mnp)(logger&));

			};

			namespace mnp { // manipulators

				logger& endl(logger& logger);
				logger& stmp(logger& logger); // time stamp

				inline namespace esc_sqn {

					logger& reset(logger& logger);

					logger& bold(logger& logger);
					logger& faint(logger& logger);
					logger& italic(logger& logger);
					logger& underline(logger& logger);
					logger& blink(logger& logger);
					logger& fast_blink(logger& logger);
					logger& rev(logger& logger);
					logger& hide(logger& logger);
					logger& cross(logger& logger);

					logger& fg_black(logger& logger);
					logger& fg_red(logger& logger);
					logger& fg_green(logger& logger);
					logger& fg_yellow(logger& logger);
					logger& fg_blue(logger& logger);
					logger& fg_magenta(logger& logger);
					logger& fg_cyan(logger& logger);
					logger& fg_white(logger& logger);

					logger& fg_b_black(logger& logger);
					logger& fg_b_red(logger& logger);
					logger& fg_b_green(logger& logger);
					logger& fg_b_yellow(logger& logger);
					logger& fg_b_blue(logger& logger);
					logger& fg_b_magenta(logger& logger);
					logger& fg_b_cyan(logger& logger);
					logger& fg_b_white(logger& logger);

					logger& bg_black(logger& logger);
					logger& bg_red(logger& logger);
					logger& bg_green(logger& logger);
					logger& bg_yellow(logger& logger);
					logger& bg_blue(logger& logger);
					logger& bg_magenta(logger& logger);
					logger& bg_cyan(logger& logger);
					logger& bg_white(logger& logger);

					logger& bg_b_black(logger& logger);
					logger& bg_b_red(logger& logger);
					logger& bg_b_green(logger& logger);
					logger& bg_b_yellow(logger& logger);
					logger& bg_b_blue(logger& logger);
					logger& bg_b_magenta(logger& logger);
					logger& bg_b_cyan(logger& logger);
					logger& bg_b_white(logger& logger);

				}

			}

		}
	}
}

#endif
