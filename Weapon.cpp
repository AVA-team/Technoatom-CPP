#include "Weapon.h"

namespace ava {

	Weapon::Weapon(sf::Vector2f position, sf::Vector2f velocity) : GameObject(position, velocity), is_need_(true) {
	}

	Weapon::~Weapon()
	{
	}

	bool Weapon::is_need() const {
		return is_need_;
	}

	void Weapon::set_is_need(bool val) {
		is_need_ = val;
	}
}