#include "Prepod.h"

namespace ava {

	const float Prepod::x_abs_velocity = 200;

	Prepod::Prepod(sf::Vector2f position)
		: GameCharacter(position, sf::Vector2f(0, x_abs_velocity)), pressed_key_(sf::Keyboard::Unknown), time_to_fire(0)
	{
		texture_.loadFromFile("Images//Ebs.jpg");
		sprite_.setTexture(texture_);
		initialize_position_and_size();
	}

	Formula* Prepod::fire(float dt) {
		time_to_fire -= dt;
		if (time_to_fire <= 0) {
			time_to_fire += 0.5;
			return new Formula(sprite_.getPosition());
		}
		else {
			return nullptr;
		}
	}

	void Prepod::set_pressed_key(sf::Keyboard::Key pressed_key) {
		pressed_key_ = pressed_key;
	}

	void Prepod::move(sf::Vector2u bound_size, float dt) {
		if (pressed_key_ == sf::Keyboard::Right) {
			velocity_ = sf::Vector2f(x_abs_velocity, 0);
		}
		else if (pressed_key_ == sf::Keyboard::Left) {
			velocity_ = sf::Vector2f(-x_abs_velocity, 0);
		}
		else {
			velocity_ = sf::Vector2f(0, 0);
		}
		GameObject::move(bound_size, dt);
	}


	Prepod::~Prepod()
	{
	}



}
