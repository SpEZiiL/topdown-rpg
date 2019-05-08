// src/cpp/include/rpg/types.hpp
/*
 * Header file for various typedefs and other type declarations.
 * 
 * Since: 2019-02-14
 * LastEdit: 2019-02-22
 * Author: Michael Federczuk
 */

#ifndef H39BDD456_8A69_4829_A2E2_F94E2F991670
#define H39BDD456_8A69_4829_A2E2_F94E2F991670

#include <string>

#define MAX_LEVEL ((game::rpg::lvl_t)100)
#define INIT_LEVEL ((game::rpg::lvl_t)1)

namespace game {
	namespace rpg {

		typedef unsigned long int hash_t;

		typedef unsigned long long int exp_t; // experience
		typedef unsigned short int lvl_t; // level
		typedef signed long int hp_t; // hitpoints

		typedef unsigned int stat_t,
				atk_t, // attack
				mag_atk_t, // magic attack
				def_t, // defense
				mag_def_t, // magic defense
				agi_t; // agility

		/**
		 * Standard base class of any other class declared for thi game.
		 * 
		 * Since: 2019-02-14
		 * LastEdit: 2019-02-22
		 * Author: Michael Federczuk
		 */
		template<class _Type>
		class std_class {

			public:
			virtual ~std_class() {
			}

			virtual std::string str() const = 0;
			virtual hash_t hash() const = 0;
			virtual bool operator==(const _Type& type) const {
				return hash() == type.hash();
			}
			virtual bool operator!=(const _Type& type) const {
				return hash() != type.hash();
			}
			virtual operator std::string() {
				return str();
			}
			virtual operator hash_t() {
				return hash();
			}

		};

		// generic concat operator for appendables
		template<class _AppendableT, class _Type>
		_AppendableT& operator+(_AppendableT& appendable,
				const std_class<_Type>& std_class) {
			return appendable + std_class.str();
		}

		// generic append operator for appendables
		template<class _AppendableT, class _Type>
		_AppendableT& operator+=(_AppendableT& appendable,
				const std_class<_Type>& std_class) {
			return appendable += std_class.str();
		}

		// generic insertion operator for streams, loggers, ...
		template<class _StreamT, class _Type>
		_StreamT& operator<<(_StreamT& stream,
				const std_class<_Type>& std_class) {
			return stream << std_class.str();
		}

	}
}

#endif
