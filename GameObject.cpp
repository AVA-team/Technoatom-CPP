#include "GameObject.h"

namespace ava {

	GameObject::GameObject(sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2f velocity = sf::Vector2f(1.F, 1.F)) :
		position_(position), velocity_(velocity) {
		texture_ = sf::Texture();
		texture_.loadFromFile("Images//default_texture.jpg");
		sprite_ = sf::Sprite(texture_);
		initialize_position_and_size();
	}

	GameObject::~GameObject()
	{
	}

	sf::Vector2f GameObject::get_position() {
		return position_;
	}

	sf::Vector2f GameObject::get_velocity() {
		return velocity_;
	}

	sf::Vector2f GameObject::get_size() const {
		return size_;
	}

	void GameObject::change_position(sf::Vector2f position) {
		position_ = position;
		sprite_.setPosition(position);
	}

	void GameObject::move(sf::Vector2u bound_size, float dt) {
		float addX = velocity_.x * dt;
		float addY = velocity_.y * dt;
		float new_x = position_.x + addX;
		float new_y = position_.y + addY;
		float x_size = (float)bound_size.x;
		float y_size = (float)bound_size.y;
		if (new_x >= 0 && new_x <= x_size) {
			position_.x = new_x;
			sprite_.move(sf::Vector2f(addX, 0));
		}
		if (new_y >= 0 && new_y <= y_size) {
			position_.y = new_y;
			sprite_.move(sf::Vector2f(0, addY));
		}
	}

	void GameObject::draw(sf::RenderTarget* target) const {
		if (target == nullptr) return;
		target->draw(sprite_);
	}

	void GameObject::initialize_position_and_size() {
		sf::FloatRect bound = sprite_.getLocalBounds();
		size_ = sf::Vector2f(bound.width, bound.height);
		sprite_.setOrigin(size_.x / 2, size_.y / 2);
		sprite_.setPosition(position_);
	}

}