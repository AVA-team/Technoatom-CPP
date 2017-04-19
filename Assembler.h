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
		uchar code_;
		bool is_argument_;
	};

	struct Register
	{
		std::string name_;
		uchar code_;
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
		void put_double_bytes_to_code(double val);
		void put_int_bytes_to_code(int val);
		uchar get_register_code(std::string reg_name);
		void generate_code_for_jmp_commands(std::string cmd_line, JUMP_COMANDS cmd_type, std::string line_number_str);
		static const int all_comands_count_ = 15;
		static const int registers_count = 4;
		ava::FileReader file_redear_;
		std::vector<std::string> source_code_;
		std::vector<uchar> code_;
		std::map<int, int> references_;
		const Comand all_comands_[all_comands_count_] =
		{
			{ "PUSH", 0, true },
			{ "PUSH_REGISTER", 1, true },
			{ "POP_REGISTER", 2, true },
			{ "ADD", 3, false },
			{ "DIV", 4, false },
			{ "MULTIPLY", 5, false },
			{ "CALL", 6, true },
			{ "RET", 7, false },
			{ "JMP", 8, true },
			{ "JMPE", 9, true },
			{ "JMPA", 10, true },
			{ "JMPAE", 11, true },
			{ "JMPB", 12, true },
			{ "JMPBE", 13, true },
			{ "JMPNE", 14, true }
		};
		const Register valid_registers[registers_count] =
		{
			{"ax", 0},
			{"bx", 1},
			{"cx", 2},
			{"dx", 3}
		};
	};
}

#endif // _ASSEMBLER_H_

