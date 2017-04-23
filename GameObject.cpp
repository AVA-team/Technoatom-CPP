#include "GameObject.h"

namespace ava {

	GameObject::GameObject() :
		position_(sf::Vector2f(0, 0)), velocity_(sf::Vector2f(1.F, 1.F)), sprite_(sf::Sprite()) {
		sprite_.setPosition(position_);
	}

	GameObject::GameObject(sf::Vector2f position, sf::Vector2f velocity = sf::Vector2f(1.F, 1.F), sf::Sprite sprite = sf::Sprite()) :
		position_(position), velocity_(velocity), sprite_(sprite) {
		sprite_.setPosition(position_);
	}

	void GameObject::move(sf::Vector2u bound_size, float dt) {
		float addX = velocity_.x * dt;
		float addY = velocity_.y * dt;
		float new_x = position_.x + addX;
		float new_y = position_.y + addY;
		if (new_x > bound_size.x) {
			position_.x = bound_size.x;
		}
		else if (new_x < 0) {
			position_.x = 0;
		}
		else {
			position_.x = new_x;
			sprite_.move(sf::Vector2f(addX, 0));
		}
		if (new_y > bound_size.y) {
			position_.y = bound_size.y;
		}
		else if (new_y < 0) {
			position_.y = 0;
		}
		else {
			position_.y = new_y;
			sprite_.move(sf::Vector2f(0, addY));
		}
	}

	void GameObject::draw(sf::RenderTarget* target) const {
		target->draw(sprite_);
	}

	GameObject::~GameObject()
	{
	}

}