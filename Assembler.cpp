#include<string>
#include<stdlib.h>
#include<cstring>
#include<sstream>
#include<iostream>
#include<fstream>
#include "Assembler.h"


namespace ava {

	std::string trim_string(std::string& str) {
		auto first = str.find_first_not_of(' '),
			last = str.find_last_not_of(' ');
		if (first == std::string::npos) {
			return str;
		}
		return str.substr(first, last - first + 1);
	}

	Assembler::Assembler(std::string file_name) {
		try {
			file_redear_.chooseFile(file_name.c_str());
		}
		catch (...) {
			crush_programm(std::string("File '") + file_name + std::string("' can not be opened...\n"));
		}
	}

	Assembler::Assembler(const char* file_name) {
		try {
			file_redear_.chooseFile(file_name);
		}
		catch (...) {
			crush_programm(std::string("File '") + file_name + std::string("' can not be opened...\n"));
		}
	}


	Assembler::~Assembler()
	{
	}

	void Assembler::generate_code() {
		define_all_references();
		auto strings_count = file_redear_.lines_count();
		std::string curr_str;
		for (size_t i = 0; i < strings_count; i++)
		{
			curr_str = file_redear_.get_line(i);
			//Если текущая строка - метка, то пропускаем её
			auto colon_pos = curr_str.find(':');
			if (colon_pos != std::string::npos) {
				continue;
			}
			generate_code_for_single_line(curr_str, i + 1);
		}
		std::ofstream of;
		std::stringstream ss;
		ss << "Byte_code" << ".txt";
		std::string fileName = ss.str();
		of.open(fileName, std::ios::out);
		auto code_lines_count = byte_code_.size();
		for (size_t i = 0; i < code_lines_count; i++)
		{
			of << byte_code_[i];
		}
		of.close();
	}

	void Assembler::generate_code_for_single_line(std::string command_line, size_t line_number) {
		std::stringstream ss;
		ss << line_number;
		std::string line_number_str = ss.str();
		std::stringstream comand_code_string;
		auto space_pos = command_line.find(' ');
		auto command = command_line.substr(0, space_pos);
		if (command == all_comands_[0].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			double val_to_push;
			try {
				val_to_push = std::stod(argument);
			}
			catch (std::exception& ex) {
				crush_programm("Error in Assembler::generate_code_for_single_line(std::string command_line): \
					illegal comand argument. Argument is not a double number\n", ex);
			}
			comand_code_string << all_comands_[0].code_ << " " << val_to_push << "\n";
			byte_code_.push_back(comand_code_string.str());
		}
		else if (command == all_comands_[1].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			int reg_code;
			try {
				reg_code = std::stoi(argument);
			}
			catch (std::exception& ex) {
				crush_programm(std::string("Error in Assembler::get_register_code(std::string reg_name):") + std::string(ex.what()) + std::string("\n Line number: ") + line_number_str);
			}
			comand_code_string << all_comands_[1].code_ << " " << reg_code << "\n";
			byte_code_.push_back(comand_code_string.str());
		}
		else if (command == all_comands_[2].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			int reg_code;
			try {
				reg_code = std::stoi(argument);
			}
			catch (std::exception& ex) {
				crush_programm(std::string("Error in Assembler::get_register_code(std::string reg_name):") + std::string(ex.what()) + std::string("\n Line number: ") + line_number_str);
			}
			
			comand_code_string << all_comands_[2].code_ << " " << reg_code << "\n";
			byte_code_.push_back(comand_code_string.str());
		}
		else if (command == all_comands_[3].name_) {
			comand_code_string << all_comands_[3].code_ << "\n";
			byte_code_.push_back(comand_code_string.str());
		}
		else if (command == all_comands_[4].name_) {
			comand_code_string << all_comands_[4].code_ << "\n";
			byte_code_.push_back(comand_code_string.str());
		}
		else if (command == all_comands_[5].name_) {
			comand_code_string << all_comands_[5].code_ << "\n";
			byte_code_.push_back(comand_code_string.str());
		}
		else if (command == all_comands_[6].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			argument = trim_string(argument);
			int flag, adress;
			try {
				flag = std::stoi(argument);
			}
			catch (...) {
				crush_programm(std::string("Error in Assembler::generate_code_for_single_line(std::string command_line): illegal flag to call.\nError line: ")
					+ line_number_str + std::string("\n"));
			}
			adress = references_[flag];
			comand_code_string << all_comands_[6].code_ << " " << adress << "\n";
			byte_code_.push_back(comand_code_string.str());
		}
		else if (command == all_comands_[7].name_) {
			comand_code_string << all_comands_[7].code_ << "\n";
			byte_code_.push_back(comand_code_string.str());
		}
		else if (command == all_comands_[8].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			argument = trim_string(argument);
			generate_code_for_jmp_commands(argument, JUMP_COMANDS::JMP, line_number_str);
		}
		else if (command == all_comands_[9].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			argument = trim_string(argument);
			generate_code_for_jmp_commands(argument, JUMP_COMANDS::JMPE, line_number_str);
		}
		else if (command == all_comands_[10].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			argument = trim_string(argument);
			generate_code_for_jmp_commands(argument, JUMP_COMANDS::JMPA, line_number_str);
		}
		else if (command == all_comands_[11].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			argument = trim_string(argument);
			generate_code_for_jmp_commands(argument, JUMP_COMANDS::JMPAE, line_number_str);
		}
		else if (command == all_comands_[12].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			argument = trim_string(argument);
			generate_code_for_jmp_commands(argument, JUMP_COMANDS::JMPB, line_number_str);
		}
		else if (command == all_comands_[13].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			argument = trim_string(argument);
			generate_code_for_jmp_commands(argument, JUMP_COMANDS::JMPBE, line_number_str);
		}
		else if (command == all_comands_[14].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			argument = trim_string(argument);
			generate_code_for_jmp_commands(argument, JUMP_COMANDS::JMPNE, line_number_str);
		}
		else if (command == all_comands_[15].name_) {
			comand_code_string << all_comands_[15].code_ << "\n";
			byte_code_.push_back(comand_code_string.str());
		}
	}

	void Assembler::define_all_references() {
		auto strings_count = file_redear_.lines_count();
		std::string curr_str;
		std::stringstream ss;
		std::string curr_line_number;
		for (size_t i = 0; i < strings_count - 1; i++)//до (strings_count - 1) тк метка не должна быть последней строкой в коде
		{
			ss << (i + 1);
			curr_line_number = ss.str();
			curr_str = file_redear_.get_line(i);
			curr_str = trim_string(curr_str);
			auto string_size = curr_str.size();
			if (string_size == 0) {
				crush_programm(std::string("Empty string in source code. Number of error line: ") + curr_line_number + std::string("\n"));
			}
			char last_char = curr_str.at(string_size - 1);
			if (last_char != ':') {
				continue;
			}
			int reference_key;
			auto argument = curr_str.substr(0, string_size - 1);
			try {
				reference_key = std::stoi(argument);
			}
			catch (std::exception& ex) {
				crush_programm(std::string("Error in Assembler::define_all_references(): failed reference value. Number of error line - \n") \
				+ curr_line_number + std::string(".\n") + std::string(ex.what()) + std::string("\n"));
			}
			auto references_count = references_.size() + 1;//+ 1 тк сейчас мы добавим текущую метку
			// +2: +1 - тк i начинается с 0 и ещё +1 - тк метка указывает на следующую после неё строку.
			//-references_count тк номер строки не должен учитывать предыдущие строки с метками
			auto actual_adress = i + 2 - references_count;
			references_.emplace(reference_key, actual_adress);
		}
	}

	void Assembler::crush_programm(const char* msg, std::exception& ex) {
		std::string msg_str(msg);
		msg_str.append(ex.what());
		crush_programm(msg_str.c_str());
	}

	void Assembler::crush_programm(const char* msg) {
		std::cerr << msg << std::endl;
		system("pause");
		exit(1);
	}

	void Assembler::crush_programm(std::string msg) {
		crush_programm(msg.c_str());
	}

	void Assembler::generate_code_for_jmp_commands(std::string argument, Assembler::JUMP_COMANDS cmd_type, std::string line_number_str) {
		std::stringstream code_string_stream;
		int flag, adress;
		try {
			flag = std::stoi(argument);
		}
		catch (...) {
			crush_programm(std::string("Error in Assembler::generate_code_for_single_line(std::string command_line): illegal flag to call.\nError line: ")
				+ line_number_str + std::string("\n"));
		}
		adress = references_[flag];
		code_string_stream << cmd_type << " " << adress << "\n";
		byte_code_.push_back(code_string_stream.str());
	}

}
