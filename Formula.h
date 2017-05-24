#ifndef _AVA_FORMULA_H_
#define _AVA_FORMULA_H_

#include"Weapon.h"

namespace ava {

	class Formula : public Weapon
	{
	public:
		Formula(sf::Vector2f position);
		~Formula();
		//! Переопределяет метод в базовом классе, так как формула движется только снизу вверх
		//!
		//! @param bound_size размер главного окна
		//! @param dt временной интервал
		void move(sf::Vector2u bound_size, float dt) override;
	private:
		static const sf::Vector2f DEFAULT_VELOCITY;
	};

}

#endif // !_AVA_FORMULA_H_