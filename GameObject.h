#ifndef _AVA_GAMEOBJECT_H_
#define _AVA_GAMEOBJECT_H_

#include <SFML/Graphics.hpp>
#include<memory>

namespace ava {
	//! Базовый класс для всех объектов игры
	class GameObject
	{
	public:
		GameObject(sf::Vector2f position, sf::Vector2f velocity);
		virtual ~GameObject();
		sf::Vector2f get_position();
		sf::Vector2f get_velocity();
		//! Изменение позиции спрайта относительно главного окна
		//!
		//! @param position - позиция относительно левого верхнего угла окна
		void change_position(sf::Vector2f position);
		//! Возвращает текущий размер спрайта
		sf::Vector2f get_size() const;
		//! Перемещает спрайт
		//! 
		//! @param bound_size размер главного окна
		//! @param dt временной интервал
		virtual void move(sf::Vector2u bound_size, float dt);
		//! Рисует объект на целевом объекты
		//!
		//! @param target целевой объект, на котором рисуется текущий объект (окно или буффер)
		virtual void draw(sf::RenderTarget* target) const;

	protected:
		//! Устанавливает начало координат в центр объекта
		//! и перемещает спрайт в заданную позицию
		void initialize_position_and_size();

		sf::Vector2f position_;
		sf::Vector2f velocity_;
		sf::Vector2f size_;
		sf::Texture texture_;
		sf::Sprite sprite_;
	};

}

#endif //_AVA_GAMEOBJECT_H_