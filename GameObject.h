#ifndef _AVA_GAMEOBJECT_H_
#define _AVA_GAMEOBJECT_H_

#include <SFML/Graphics.hpp>
#include<memory>

namespace ava {
	//! ������� ����� ��� ���� �������� ����
	class GameObject
	{
	public:
		GameObject(sf::Vector2f position, sf::Vector2f velocity);
		virtual ~GameObject();
		sf::Vector2f get_position();
		sf::Vector2f get_velocity();
		//! ��������� ������� ������� ������������ �������� ����
		//!
		//! @param position - ������� ������������ ������ �������� ���� ����
		void change_position(sf::Vector2f position);
		//! ���������� ������� ������ �������
		sf::Vector2f get_size() const;
		//! ���������� ������
		//! 
		//! @param bound_size ������ �������� ����
		//! @param dt ��������� ��������
		virtual void move(sf::Vector2u bound_size, float dt);
		//! ������ ������ �� ������� �������
		//!
		//! @param target ������� ������, �� ������� �������� ������� ������ (���� ��� ������)
		virtual void draw(sf::RenderTarget* target) const;

	protected:
		//! ������������� ������ ��������� � ����� �������
		//! � ���������� ������ � �������� �������
		void initialize_position_and_size();

		sf::Vector2f position_;
		sf::Vector2f velocity_;
		sf::Vector2f size_;
		sf::Texture texture_;
		sf::Sprite sprite_;
	};

}

#endif //_AVA_GAMEOBJECT_H_