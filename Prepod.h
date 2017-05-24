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
		//! ������� ��������
		//!
		//! @param dt ��������� ��������
		//! @return ������������ �������
		Formula* fire(float dt);
		//! ������������� �������, ������� ������ � ������ ������
		//!
		//! @param pressed_key �������, ������� ������ � ������ ������
		void set_pressed_key(sf::Keyboard::Key pressed_key);
		//! �������������� ����� � ������� ������, ��� ��� ������ �������� ������ ����� � ������
		//!
		//! @param bound_size ������ �������� ����
		//! @param dt ��������� ��������
		void move(sf::Vector2u bound_size, float dt) override;
	private:
		static const float x_abs_velocity;
		float time_to_fire;
		sf::Keyboard::Key pressed_key_;
	};

}

#endif // !_AVA_PREPOD_H_
