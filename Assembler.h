#ifndef _ASSEMBLER_H_
#define _ASSEMBLER_H_

#include <string>
#include <map>
#include <fstream>
#include "command.h"

namespace ava {

	class Assembler
	{
	public:
		Assembler(std::string file_name);
		void compile();
		~Assembler();

	private:
		const char symbol_of_reference_ = ':';
		std::string source_filename_;
		std::string destination_filename_;
		std::ifstream fin_;
		std::ofstream fout_;
		std::map<int, int> references_;
		void define_all_references();
		void parse_in_output();
		bool in_jmps_commands(Command_code code);
	};
}

#endif // _ASSEMBLER_H_

