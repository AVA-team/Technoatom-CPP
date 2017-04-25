#include <iostream>
#include "processor.h"

int main() {
	int num_of_factorial = 0;
	std::cout << "Enter number for factorial process:";
	std::cin >> num_of_factorial;
	try {
		ava::Processor cpu("assembly_factorial.txt");
		cpu.set_data_stack({ num_of_factorial });
		cpu.process();
		cpu.show_state();
	}
	catch (std::exception & ex) {
		std::cerr << ex.what();
	}
	system("pause");
	return 0;
}