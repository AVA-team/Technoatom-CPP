#ifndef _AVA_PREPOD_H_
#define _AVA_PREPOD_H_

#include"GameCharacter.h"
#include"Formula.h"


namespace ava {

	class Prepod : public GameCharacter
	{
	public:
		Prepod(sf::Vector2f position);
		~Prepod();
		//! Выстрел формулой
		//!
		//! @param dt временной интервал
		//! @return выстреленная формула
		Formula* fire(float dt);
		//! Устанавливает клавишу, которая нажата в данный момент
		//!
		//! @param pressed_key клавиша, которая нажата в данный момент
		void set_pressed_key(sf::Keyboard::Key pressed_key);
		//! Переопределяет метод в базовом классе, так как препод движется только влево и вправо
		//!
		//! @param bound_size размер главного окна
		//! @param dt временной интервал
		void move(sf::Vector2u bound_size, float dt) override;
	private:
		static const float x_abs_velocity;
		float time_to_fire;
		sf::Keyboard::Key pressed_key_;
	};

}

#endif // !_AVA_PREPOD_H_
