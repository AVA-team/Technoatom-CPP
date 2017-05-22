#include "GameCharacter.h"

namespace ava {

	GameCharacter::GameCharacter(sf::Vector2f position, sf::Vector2f velocity = sf::Vector2f(1.0F, 1.0F)) :
		GameObject(position, velocity), hp_(INITIAL_HP){ }

	GameCharacter::~GameCharacter(){ }

	void GameCharacter::damage() {
		hp_ -= ONE_HIT_DAMAGE;
	}

	bool GameCharacter::is_die() {
		return hp_ <= 0;
	}
}
