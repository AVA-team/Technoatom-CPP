#include<iostream>
#include<string>
#include<vector>
#include"Assembler.h"

int main(int argc, char** argv) {
	if (argc < 2) {
		return 0;
	}
	ava::Assembler ass(argv[1]);
	ass.generate_code();
	std::cout << "Programm sucessfuly compiled and saved in the current directory\n";
	system("pause");
	return 0;
}