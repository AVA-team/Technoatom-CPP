#include <iostream>
#include "processor.h"

int main(int argc, char** argv) {
	try {
		ava::Processor cpu("assembly_factorial.txt");
		cpu.set_data_stack({ 5 });
		cpu.process();
		cpu.show_state();
	}
	catch (std::exception & ex) {
		std::cerr << ex.what();
	}
	system("pause");
	return 0;
}