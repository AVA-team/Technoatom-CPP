#include <iostream>
#include "auto_ptr.h"
using ava::auto_ptr;

int main() {
	//GIVEN
	auto_ptr<int> p1(new int(1));
	std::cout << "p1 = " << p1.get() << std::endl;
	//WHEN
	auto_ptr<int> p2;
	p2 = p1;
	//THEN
	std::cout << "p2 = " << p2.get() << std::endl;
	std::cout << "p1 = " << p1.get() << std::endl;
	system("PAUSE");
	return 0;
}