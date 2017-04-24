#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_

#include <string>
#include <map>
#include <fstream>
#include "command.h"

namespace ava
{
	class Assembler
	{
	public:
		Assembler();
		Assembler(const std::string & source_file_name, const std::string & destination_file_name = std::string());
		//! delete copy constructor, because fstreams can't be copyd
		Assembler(const Assembler &) = delete;
		//! delete assigment operator, because fstreams can't be assigment
		Assembler & operator= (const Assembler &) = delete;
		void source_bind(const std::string & file_name);
		void destination_bind(const std::string & file_name);
		void compile();
		~Assembler();
	private:
		const char symbol_of_reference_ = ':';
		std::string source_filename_;
		std::string destination_filename_;
		std::ifstream fin_;
		std::ofstream fout_;
		std::map<int, int> references_;
		void close_file_streams();
		void define_all_references();
		void parse_in_output();
		bool in_jmps_commands(Command_code code) const;
	};
}

#endif // ASSEMBLER_H_

