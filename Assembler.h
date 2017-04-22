#ifndef _ASSEMBLER_H_
#define _ASSEMBLER_H_

#include<string>
#include<map>
#include<vector>
#include"FileReader.h"

namespace ava {

	typedef unsigned char uchar;

	struct Comand
	{
		std::string name_;
		int code_;
		bool is_argument_;
	};

	class Assembler
	{
	public:
		Assembler(std::string file_name);
		Assembler(const char* file_name);
		void generate_code();
		~Assembler();

	private:
		enum JUMP_COMANDS {
			JMP = 8,
			JMPE,
			JMPA,
			JMPAE,
			JMPB,
			JMPBE,
			JMPNE
		};
		void generate_code_for_single_line(std::string line, size_t line_number);
		void define_all_references();
		void crush_programm(const char* msg, std::exception& ex);
		void crush_programm(const char* msg);
		void crush_programm(std::string msg);
		void generate_code_for_jmp_commands(std::string cmd_line, JUMP_COMANDS cmd_type, std::string line_number_str);
		static const int ALL_COMANDS_COUNT_ = 16;
		ava::FileReader file_redear_;
		std::vector<std::string> source_code_;
		std::vector<std::string> byte_code_;
		std::map<int, int> references_;
		const Comand all_comands_[ALL_COMANDS_COUNT_] =
		{
			{ "push", 0, true },
			{ "push_register", 1, true },
			{ "pop_register", 2, true },
			{ "add", 3, false },
			{ "div", 4, false },
			{ "multiply", 5, false },
			{ "call", 6, true },
			{ "ret", 7, false },
			{ "jmp", 8, true },
			{ "jmpe", 9, true },
			{ "jmpa", 10, true },
			{ "jmpae", 11, true },
			{ "jmpb", 12, true },
			{ "jmpbe", 13, true },
			{ "jmpne", 14, true },
			{"end", 15, false }
		};
	};
}

#endif // _ASSEMBLER_H_

