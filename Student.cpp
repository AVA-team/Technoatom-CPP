#include "Student.h"

namespace ava {

	const sf::Vector2f Student::DEFAULT_VELOCITY = sf::Vector2f(0, 3.0F);

	Student::Student(sf::Vector2f position) : GameCharacter(position, DEFAULT_VELOCITY)
	{
		texture_.loadFromFile("Images//student.jpg");
		sprite_.setTexture(texture_);
		initialize_position_and_size();
	}


	Student::~Student()
	{
	}

}