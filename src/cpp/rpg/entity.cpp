// src/cpp/rpg/entity.cpp
/*
 * entity.hpp implementation.
 * Source file for a generic entity with stats.
 * 
 * Since: 2019-02-21
 * LastEdit: 2019-02-22
 */

#include <rpg/entity.hpp>
#include <util/utils.hpp>

namespace game {
	namespace rpg {

		entity::entity()
				: name("unnamed_entity"), lvl(0), max_hp(0), hp(0), atk(0),
						mag_atk(0), def(0), mag_def(0), agi(0) {
		}

		entity::entity(std::string name, lvl_t lvl, hp_t max_hp, hp_t hp,
				atk_t atk, mag_atk_t mag_atk, def_t def, mag_def_t mag_def,
				agi_t agi)
				: name(name), lvl(lvl), max_hp(max_hp), hp(hp), atk(atk),
						mag_atk(mag_atk), def(def), mag_def(mag_def), agi(agi) {
		}

		entity::~entity() {
		}

		/* ================================================================= */

		std::string entity::get_name() const {
			return name;
		}
		void entity::set_name(std::string name) {
			this->name = name;
		}

		lvl_t entity::get_lvl() const {
			return lvl;
		}
		void entity::set_lvl(lvl_t lvl) {
			this->lvl = lvl;
		}

		hp_t entity::get_max_hp() const {
			return max_hp;
		}
		void entity::set_max_hp(hp_t max_hp) {
			this->max_hp = max_hp;
		}

		hp_t entity::get_hp() const {
			return hp;
		}
		void entity::set_hp(hp_t hp) {
			this->hp = hp;
		}

		atk_t entity::get_atk() const {
			return atk;
		}
		void entity::set_atk(atk_t atk) {
			this->atk = atk;
		}

		mag_atk_t entity::get_mag_atk() const {
			return mag_atk;
		}
		void entity::set_mag_atk(mag_atk_t mag_atk) {
			this->mag_atk = mag_atk;
		}

		def_t entity::get_def() const {
			return def;
		}
		void entity::set_def(def_t def) {
			this->def = def;
		}

		mag_def_t entity::get_mag_def() const {
			return mag_def;
		}
		void entity::set_mag_def(mag_def_t mag_def) {
			this->mag_def = mag_def;
		}

		agi_t entity::get_agi() const {
			return agi;
		}
		void entity::set_agi(agi_t agi) {
			this->agi = agi;
		}

		/* ================================================================= */

		std::string entity::str() const {
			std::string str;

			using game::util::operator+;

			str = str + "Entity \"" + name + "\" lvl: " + lvl + '\n'
					+ "HP: " + hp + '/' + max_hp + '\n'
					+ "Attack: " + atk + '\n'
					+ "Magic Attack: " + mag_atk + '\n'
					+ "Defense: " + def + '\n'
					+ "Magic Defense: " + mag_def + '\n'
					+ "Agility: " + agi;

			return str;
		}

		hash_t entity::hash() const {
			hash_t result = 1;

			for(size_t i = 0, len = name.length(); i < len; ++i) {
				result = 31 * result + name[i];
			}

			result = 31 * result + lvl;
			result = 31 * result + max_hp;
			result = 31 * result + hp;
			result = 31 * result + atk;
			result = 31 * result + mag_atk;
			result = 31 * result + def;
			result = 31 * result + mag_def;
			result = 31 * result + agi;

			return result;
		}

		bool entity::operator==(const entity& e) const {
			return e.name == name
					&& e.lvl == lvl
					&& e.max_hp == max_hp
					&& e.hp == hp
					&& e.atk == atk
					&& e.mag_atk == mag_atk
					&& e.def == def
					&& e.mag_def == def
					&& e.agi == agi;
		}
		bool entity::operator!=(const entity& e) const {
			return e.name != name
					|| e.lvl != lvl
					|| e.max_hp != max_hp
					|| e.hp != hp
					|| e.atk != atk
					|| e.mag_atk != mag_atk
					|| e.def != def
					|| e.mag_def != def
					|| e.agi != agi;
		}

	}
}
