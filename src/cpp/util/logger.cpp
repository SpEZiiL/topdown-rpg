// src/cpp/util/logger.cpp
/*
 * logger.hpp implementation.
 * Source file for the logger object.
 * 
 * Since: 2019-02-17
 * LastEdit: 2019-02-21
 */

#include <util/logger.hpp>

#define _esc_sqn(name, code) \
		game::util::log::logger& name(game::util::log::logger& l) { \
			if(l.esc_sqn_enabled()) l << "\033[" #code "m"; \
			return l;\
		}

namespace game {
	namespace util {
		inline namespace log {

			logger::logger(ostream& stream, bool esc_sqn)
					: stream(stream), esc_sqn_on(esc_sqn) {
			}

			/* ================================================================= */

			const ostream& logger::get_stream() {
				return stream;
			}
			const ostream& logger::operator*() {
				return stream;
			}

			bool logger::esc_sqn_enabled() {
				return esc_sqn_on;
			}

			/* ================================================================= */

			logger& logger::operator<<(std::string str) {
				stream << str;
				return *this;
			}

			logger& logger::operator<<(bool b) {
				stream << (b ? "true" : "false");
				return *this;
			}

			logger& logger::operator<<(signed short int h) {
				stream << h;
				return *this;
			}

			logger& logger::operator<<(signed int i) {
				stream << i;
				return *this;
			}

			logger& logger::operator<<(signed long int l) {
				stream << l;
				return *this;
			}

			logger& logger::operator<<(signed long long int ll) {
				stream << ll;
				return *this;
			}

			logger& logger::operator<<(unsigned short int hu) {
				stream << hu;
				return *this;
			}

			logger& logger::operator<<(unsigned int u) {
				stream << u;
				return *this;
			}

			logger& logger::operator<<(unsigned long int lu) {
				stream << lu;
				return *this;
			}

			logger& logger::operator<<(unsigned long long int llu) {
				stream << llu;
				return *this;
			}

			logger& logger::operator<<(float f) {
				stream << f;
				return *this;
			}

			logger& logger::operator<<(double f) {
				stream << f;
				return *this;
			}

			logger& logger::operator<<(long double lf) {
				stream << lf;
				return *this;
			}

			logger& logger::operator<<(signed char c) {
				stream << c;
				return *this;
			}

			logger& logger::operator<<(unsigned char uc) {
				stream << uc;
				return *this;
			}

			logger& logger::operator<<(const char* s) {
				stream << s;
				return *this;
			}

			logger& logger::operator<<(const void* p) {
				stream << p;
				return *this;
			}

			logger& logger::operator<<(ostream& (*mnp)(ostream&)) {
				stream << mnp;
				return *this;
			}

			logger& logger::operator<<(logger& (*mnp)(logger&)) {
				return mnp(*this);
			}

			/* ================================================================= */

			namespace mnp {

				logger& endl(logger& logger) {
					if(logger.esc_sqn_enabled()) logger << "\033[0m";
					logger << std::endl;
					return logger;
				}

				logger& stmp(logger& logger) {
					if(logger.esc_sqn_enabled()) logger << "\033[40m";
					logger << "[HH:mm:ss.SSS] "; // TODO rpg-game: logger.cpp: game::util::log::mnp::stmp(logger&): timestamp
					if(logger.esc_sqn_enabled()) logger << "\033[0m";
					return logger;
				}

				inline namespace esc_sqn {

					_esc_sqn(reset, 0);

					_esc_sqn(bold, 1);
					_esc_sqn(faint, 2);
					_esc_sqn(italic, 3);
					_esc_sqn(underline, 4);
					_esc_sqn(blink, 5);
					_esc_sqn(fast_blink, 6);
					_esc_sqn(rev, 7);
					_esc_sqn(hide, 8);
					_esc_sqn(cross, 9);

					_esc_sqn(fg_black, 30);
					_esc_sqn(fg_red, 31);
					_esc_sqn(fg_green, 32);
					_esc_sqn(fg_yellow, 33);
					_esc_sqn(fg_blue, 34);
					_esc_sqn(fg_magenta, 35);
					_esc_sqn(fg_cyan, 36);
					_esc_sqn(fg_white, 37);

					_esc_sqn(bg_black, 40);
					_esc_sqn(bg_red, 41);
					_esc_sqn(bg_green, 42);
					_esc_sqn(bg_yellow, 43);
					_esc_sqn(bg_blue, 44);
					_esc_sqn(bg_magenta, 45);
					_esc_sqn(bg_cyan, 46);
					_esc_sqn(bg_white, 47);

					_esc_sqn(fg_b_black, 90);
					_esc_sqn(fg_b_red, 91);
					_esc_sqn(fg_b_green, 92);
					_esc_sqn(fg_b_yellow, 93);
					_esc_sqn(fg_b_blue, 94);
					_esc_sqn(fg_b_magenta, 95);
					_esc_sqn(fg_b_cyan, 96);
					_esc_sqn(fg_b_white, 97);

					_esc_sqn(bg_b_black, 100);
					_esc_sqn(bg_b_red, 101);
					_esc_sqn(bg_b_green, 102);
					_esc_sqn(bg_b_yellow, 103);
					_esc_sqn(bg_b_blue, 104);
					_esc_sqn(bg_b_magenta, 105);
					_esc_sqn(bg_b_cyan, 106);
					_esc_sqn(bg_b_white, 107);

				}

			}

		}
	}
}

#undef _esc_sqn
