#ifndef _AVA_GAME_ENGINE_H_
#define _AVA_GAME_ENGINE_H_

#include<vector>
#include<memory>
#include"Prepod.h"
#include"Student.h"

namespace ava {
	//! Игровой движок
	class GameEngine
	{
	public:
		GameEngine(sf::Vector2u bound_size);
		~GameEngine();
		//! Производит одну итерацию движка
		//! 
		//! @param pressed_key нажатая клавиша
		//! @param dt время, прошедшее с момента последней итерации
		void do_iteration(sf::Keyboard::Key pressed_key, float dt);
		//! Отрисовка всех активных элементов
		//!
		//! @param target целевой объект на котором всё рисуется (окно или буффер)
		void draw_scene(sf::RenderTarget* target);
		//! Выстрел
		//!
		//! @param dt время, прошедшее с момента последней итерации 
		void fire(float dt);
		//! Обновить размер главного окна
		//!
		//! @param val новый размер главного окна
		void update_bound_size(sf::Vector2u val);
		//! Проверяет закончена ли игра
		bool is_game_over() const;
		//! Проверяет выиграл ли препод
		bool is_ebs_win() const;

	private:
		static const float ENIMY_CREATION_PERIOD; //s
		void check_student_damage();
		void create_new_enimy();
		bool is_game_over_, is_ebs_win_;
		float time_;
		sf::Vector2u bound_size_;
		std::vector<std::shared_ptr<Student>> enimies_;
		std::vector<std::unique_ptr<Formula>> formulas_;
		std::unique_ptr<Prepod> ebs_;
	};

}

#endif


