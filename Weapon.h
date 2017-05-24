#ifndef _AVA_WEAPON_H_
#define _AVA_WEAPON_H_

#include"GameObject.h"

namespace ava {
	//! Базовый класс для оружия
	class Weapon : public GameObject
	{
	public:
		Weapon(sf::Vector2f position, sf::Vector2f velocity);
		~Weapon();
		//! Определяет нужно ли оружие на данный момент
		//!
		//! @return нужно ли оружие
		bool is_need() const;
		//! Устанавливает переменную, которая определяет нужно ли оружие
		//!
		//! @param val нужно ли оружие
		void set_is_need(bool val);
	private:
		bool is_need_;
	};

}

#endif // !_AVA_WEAPON_H_