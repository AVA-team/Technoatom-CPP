#include "Formula.h"

namespace ava {

	const sf::Vector2f Formula::DEFAULT_VELOCITY = sf::Vector2f(0, -200.0F);

	Formula::Formula(sf::Vector2f position) : Weapon(position, DEFAULT_VELOCITY) {
		texture_.loadFromFile("Images//formula_mini.jpg");
		sprite_.setTexture(texture_);
		sprite_.setTextureRect(sf::IntRect(0, 0, texture_.getSize().x, texture_.getSize().y));
		initialize_position_and_size();
	}


	Formula::~Formula() {

	}

	void Formula::move(sf::Vector2u bound_size, float dt) {
		float addX = velocity_.x * dt;
		float addY = velocity_.y * dt;
		position_.x = position_.x + addX;
		position_.y = position_.y + addY;
		sprite_.move(sf::Vector2f(addX, addY));
	}
}