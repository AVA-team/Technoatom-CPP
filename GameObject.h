#ifndef _AVA_GAMEOBJECT_H_
#define _AVA_GAMEOBJECT_H_

#include <SFML/Graphics.hpp>

namespace ava {

	class GameObject
	{
	public:
		GameObject();
		GameObject(sf::Vector2f position, sf::Vector2f velocity = sf::Vector2f(1.F, 1.F), sf::Sprite sprite = sf::Sprite());
		void move(sf::Vector2u bound_size, float dt);
		virtual void draw(sf::RenderTarget* target) const;
		virtual ~GameObject();

	protected:
		sf::Vector2f position_;
		sf::Vector2f velocity_;
		sf::Sprite sprite_;
	};

}

#endif //_AVA_GAMEOBJECT_H_