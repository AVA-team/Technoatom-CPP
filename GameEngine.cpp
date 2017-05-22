#include<algorithm>
#include "GameEgine.h"

namespace ava {

	const float GameEngine::ENIMY_CREATION_PERIOD = 7.0F;//s

	GameEngine::GameEngine(sf::Vector2u bound_size) :
	is_game_over_(false), is_ebs_win_(false), time_(0) {
		bound_size_ = bound_size;
		ebs_ = std::unique_ptr<Prepod>(new Prepod(sf::Vector2f(0, 0)));
		float ebs_init_x_pos = (float)bound_size_.x / 2,
			ebs_init_y_pos = (float)bound_size_.y - ((float)ebs_->get_size().y / 2);
		ebs_->change_position(sf::Vector2f(ebs_init_x_pos, ebs_init_y_pos));
		enimies_.push_back(std::shared_ptr<Student>(new Student(sf::Vector2f(ebs_init_x_pos, 0))));
	}


	GameEngine::~GameEngine() {

	}

	void GameEngine::do_iteration(sf::Keyboard::Key pressed_key, float dt) {
		if (is_game_over_) {
			return;
		}
		time_ += dt;
		ebs_->set_pressed_key(pressed_key);
		ebs_->move(bound_size_, dt);
		std::for_each(formulas_.begin(), formulas_.end(), [this, dt](std::unique_ptr<Formula>& formula) {formula->move(bound_size_, dt); });
		check_student_damage();
		std::for_each(enimies_.begin(), enimies_.end(), [this, dt](std::shared_ptr<Student>& student) {student->move(bound_size_, dt); });
		if (time_ >= ENIMY_CREATION_PERIOD) {
			create_new_enimy();
			time_ = 0;
		}
		auto alive_student = std::find_if(enimies_.begin(), enimies_.end(), [this](std::shared_ptr<Student>& student)->bool {return student->get_position().y >= bound_size_.y; });
		if (alive_student != enimies_.end()) {
			is_game_over_ = true;
		}
	}

	void GameEngine::check_student_damage() {
		for (auto formula_iterator = formulas_.begin(); formula_iterator != formulas_.end(); ++formula_iterator) {
			if (!(*formula_iterator)->is_need()) {
				continue;
			}
			auto damaged_student = std::find_if(enimies_.begin(), enimies_.end(), [formula_iterator](std::shared_ptr<Student>& student) -> bool {
				auto student_pos = student->get_position();
				auto student_size = student->get_size();
				auto formula_size = (*formula_iterator)->get_size();
				auto formula_pos = (*formula_iterator)->get_position();
				// check condition of formula-student intersection !!!
				return (formula_pos.x >= student_pos.x - (student_size.x / 2)) && (formula_pos.x <= student_pos.x + (student_size.x / 2))
					&& ((formula_pos.y - (formula_size.y / 2)) <= (student_pos.y + (student_size.y / 2)))
					&& ((formula_pos.y + (formula_size.y / 2)) >= (student_pos.y - (student_size.y / 2)));
			});
			if (damaged_student == enimies_.end()) {
				continue;
			}
			(*damaged_student)->damage();
			(*formula_iterator)->set_is_need(false);
		}
		formulas_.erase(std::remove_if(formulas_.begin(), formulas_.end(), [](std::unique_ptr<Formula>& formula) -> bool {return !formula->is_need(); }), formulas_.end());
		enimies_.erase(std::remove_if(enimies_.begin(), enimies_.end(), [](std::shared_ptr<Student>& student) -> bool {return student->is_die(); }), enimies_.end());
	}

	void GameEngine::fire() {
		formulas_.push_back(std::unique_ptr<Formula>(ebs_->fire()));
	}

	void GameEngine::draw_scene(sf::RenderTarget* target) {
		if (target == nullptr) {
			return;
		}
		ebs_->draw(target);
		std::for_each(formulas_.begin(), formulas_.end(), [target](std::unique_ptr<Formula>& formula) {formula->draw(target); });
		std::for_each(enimies_.begin(), enimies_.end(), [target](std::shared_ptr<Student>& student) {student->draw(target); });
	}

	bool GameEngine::is_game_over() const {
		return is_game_over_;
	}

	bool GameEngine::is_ebs_win() const {
		return is_ebs_win_;
	}

	void GameEngine::create_new_enimy() {
		float x_pos = (float)(std::rand() % bound_size_.x);
		enimies_.push_back(std::shared_ptr<Student>(new Student(sf::Vector2f(x_pos, 0))));
	}

	void GameEngine::update_bound_size(sf::Vector2u val) {
		bound_size_ = val;
	}

}