// src/cpp/include/rpg/header.hpp
/*
 * Header file for a generic entity with stats.
 * 
 * Since 2019-02-14
 * LastEdit: 2019-02-22
 * Author: Michael Federczuk
 */

#ifndef H27889A80_3F9D_4161_BE5E_8BB08ECA933F
#define H27889A80_3F9D_4161_BE5E_8BB08ECA933F

#include <rpg/types.hpp>

namespace game {
	namespace rpg {

		/**
		 * A generic entity with stats.
		 * 
		 * Since: 2019-02-14
		 * LastEdit: 2019-02-22
		 * Author: Michael Federczuk
		 */
		class entity : public std_class<entity> {

			private:
			std::string name;
			lvl_t lvl;
			hp_t max_hp;
			hp_t hp;
			atk_t atk;
			mag_atk_t mag_atk;
			def_t def;
			mag_def_t mag_def;
			agi_t agi;

			public:
			entity();
			entity(std::string name, lvl_t lvl, hp_t max_hp, hp_t hp,
					atk_t atk, mag_atk_t mag_atk, def_t def, mag_def_t mag_def,
					agi_t agi);
			~entity();

			std::string get_name() const;
			void set_name(std::string name);

			lvl_t get_lvl() const;
			void set_lvl(lvl_t lvl);

			hp_t get_max_hp() const;
			void set_max_hp(hp_t max_hp);

			hp_t get_hp() const;
			void set_hp(hp_t hp);

			atk_t get_atk() const;
			void set_atk(atk_t atk);

			mag_atk_t get_mag_atk() const;
			void set_mag_atk(mag_atk_t mag_atk);

			def_t get_def() const;
			void set_def(def_t def);

			mag_def_t get_mag_def() const;
			void set_mag_def(mag_def_t mag_def);

			agi_t get_agi() const;
			void set_agi(agi_t agi);

			/* ================================================================= */

			std::string str() const;

			hash_t hash() const;

			bool operator==(const entity& entity) const;
			bool operator!=(const entity& entity) const;

		};

	}
}

#endif
