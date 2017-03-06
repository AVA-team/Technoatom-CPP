#include <iostream>
#include "Array.h"

int main(){
	ava::Vector<int> v1;

	v1.fill(3);
	ava::Vector<int> v2(5);
	v2.fill(6);

	v1.swap(v2);

	//v2 = v1;

	v1.dump();
	v2.dump();

	//////////
	ava::Array<int, 6> a1, a2;
	a1.fill(1);
	a2.fill(2);

	a1.swap(a2);

	//a2 = a1;

	a1.dump();
	a2.dump();
	try{
		a1.at(10);
	}
	catch(std::exception & ex){
		std::cout << ex.what() << std::endl;
	}

	system("PAUSE");
	return 0;
}