#ifndef _AVA_STUDENT_H_
#define _AVA_STUDENT_H_

#include"GameCharacter.h"

namespace ava {

	class Student : public GameCharacter
	{
	public:
		Student(sf::Vector2f position);
		~Student();
	private:
		static const sf::Vector2f DEFAULT_VELOCITY;
	};

}

#endif//_AVA_STUDENT_H_