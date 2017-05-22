#ifndef _AVA_GAME_ENGINE_H_
#define _AVA_GAME_ENGINE_H_

#include<vector>
#include<memory>
#include"Prepod.h"
#include"Student.h"

namespace ava {

	class GameEngine
	{
	public:
		GameEngine(sf::Vector2u bound_size);
		~GameEngine();
		void do_iteration(sf::Keyboard::Key pressed_key, float dt);
		void draw_scene(sf::RenderTarget* target);
		void fire();
		void update_bound_size(sf::Vector2u val);
		bool is_game_over() const;
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


