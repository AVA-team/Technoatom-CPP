#ifndef _AVA_WEAPON_H_
#define _AVA_WEAPON_H_

#include"GameObject.h"

namespace ava {

	class Weapon : public GameObject
	{
	public:
		Weapon(sf::Vector2f position, sf::Vector2f velocity);
		~Weapon();
		bool is_need() const;
		void set_is_need(bool val);
	private:
		bool is_need_;
	};

}

#endif // !_AVA_WEAPON_H_