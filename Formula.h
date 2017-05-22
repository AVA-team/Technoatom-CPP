#ifndef _AVA_FORMULA_H_
#define _AVA_FORMULA_H_

#include"Weapon.h"

namespace ava {

	class Formula : public Weapon
	{
	public:
		Formula(sf::Vector2f position);
		~Formula();
		void move(sf::Vector2u bound_size, float dt) override;
	private:
		static const sf::Vector2f DEFAULT_VELOCITY;
	};

}

#endif // !_AVA_FORMULA_H_