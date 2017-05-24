#ifndef _AVA_GAME_CHARACTER_H_
#define _AVA_GAME_CHARACTER_H_

#include"GameObject.h"

namespace ava {
	//! Базовый класс для персонажей игры
	class GameCharacter : public GameObject
	{
	public:
		const static int INITIAL_HP = 100, ONE_HIT_DAMAGE = 50;
		GameCharacter(sf::Vector2f position, sf::Vector2f velocity);
		~GameCharacter();
		//! Наносит урон текущему объекту
		void damage();
		//! Проверяет мёртв ли персонаж
		//!
		//! @return значение, указывающее мёртв ли персонаж
		bool is_die();
	protected:
		int hp_;
	};

}

#endif //_AVA_GAME_CHARACTER_H_