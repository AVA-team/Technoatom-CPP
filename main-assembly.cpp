#include <iostream>
#include "assembler.h"

int main(int argc, char** argv) {
	if (argc < 2) {
		return 0;
	}
	try {
		ava::Assembler asmb(argv[1]);
		asmb.compile();
	}
	catch (std::exception & ex) {
		std::cerr << ex.what();
	}
	system("pause");
	return 0;
}