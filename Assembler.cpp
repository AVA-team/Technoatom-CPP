#include<string>
#include<stdlib.h>
#include<cstring>
#include<sstream>
#include<iostream>
#include<fstream>
#include "Assembler.h"


namespace ava {


	Assembler::Assembler(std::string file_name) {
		try {
			file_redear_.chooseFile(file_name.c_str());
		}
		catch (...) {
			crush_programm(std::string("File '") + file_name + std::string("' does not exist...\n"));
		}
	}

	Assembler::Assembler(const char* file_name) {
		try {
			file_redear_.chooseFile(file_name);
		}
		catch (...) {
			crush_programm(std::string("File '") + file_name + std::string("' does not exist...\n"));
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
		of.open(std::string("Byte_code_") + std::string(__TIME__) + std::string(".txt"));
		auto bytes_count = code_.size();
		for (size_t i = 0; i < bytes_count; i++)
		{
			of << code_[i];
		}
		of.close();
	}

	void Assembler::generate_code_for_single_line(std::string command_line, size_t line_number) {
		std::stringstream ss;
		ss << line_number;
		std::string line_number_str = ss.str();
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
			code_.push_back(all_comands_[0].code_);
			put_double_bytes_to_code(val_to_push);
		}
		else if (command == all_comands_[1].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			uchar reg_code;
			try {
				reg_code = get_register_code(argument);
			}
			catch (std::invalid_argument& ex) {
				crush_programm(std::string("Error in Assembler::get_register_code(std::string reg_name):") + std::string(ex.what()));
			}
			code_.push_back(all_comands_[1].code_);
			code_.push_back(reg_code);
		}
		else if (command == all_comands_[2].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			uchar reg_code;
			try {
				reg_code = get_register_code(argument);
			}
			catch (std::invalid_argument& ex) {
				crush_programm(std::string("Error in Assembler::get_register_code(std::string reg_name):") + std::string(ex.what()));
			}
			code_.push_back(all_comands_[2].code_);
			code_.push_back(reg_code);
		}
		else if (command == all_comands_[3].name_) {
			code_.push_back(all_comands_[3].code_);
		}
		else if (command == all_comands_[4].name_) {
			code_.push_back(all_comands_[4].code_);
		}
		else if (command == all_comands_[5].name_) {
			code_.push_back(all_comands_[5].code_);
		}
		else if (command == all_comands_[6].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			auto colon_pos = argument.find(':');
			if (colon_pos == std::string::npos) {
				crush_programm(std::string("Error in Assembler::generate_code_for_single_line(std::string command_line): \
								illegal CALL comand\nLine number: ") + line_number_str);
			}
			auto flag_to_call = argument.substr(colon_pos + 1, std::string::npos);
			int flag, adress;
			try {
				flag = std::stoi(flag_to_call);
			}
			catch (...) {
				crush_programm(std::string("Error in Assembler::generate_code_for_single_line(std::string command_line): illegal flag to call.\nError line: ")
					+ line_number_str + std::string("\n"));
			}
			adress = references_[flag];
			code_.push_back(all_comands_[6].code_);
			put_int_bytes_to_code(adress);
		}
		else if (command == all_comands_[7].name_) {
			code_.push_back(all_comands_[7].code_);
		}
		else if (command == all_comands_[8].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			generate_code_for_jmp_commands(argument, JUMP_COMANDS::JMP, line_number_str);
		}
		else if (command == all_comands_[9].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			generate_code_for_jmp_commands(argument, JUMP_COMANDS::JMPE, line_number_str);
		}
		else if (command == all_comands_[10].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			generate_code_for_jmp_commands(argument, JUMP_COMANDS::JMPA, line_number_str);
		}
		else if (command == all_comands_[11].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			generate_code_for_jmp_commands(argument, JUMP_COMANDS::JMPAE, line_number_str);
		}
		else if (command == all_comands_[12].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			generate_code_for_jmp_commands(argument, JUMP_COMANDS::JMPB, line_number_str);
		}
		else if (command == all_comands_[13].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			generate_code_for_jmp_commands(argument, JUMP_COMANDS::JMPBE, line_number_str);
		}
		else if (command == all_comands_[14].name_) {
			auto argument = command_line.substr(space_pos + 1, std::string::npos);
			generate_code_for_jmp_commands(argument, JUMP_COMANDS::JMPNE, line_number_str);
		}
	}

	void Assembler::define_all_references() {
		auto strings_count = file_redear_.lines_count();
		std::string curr_str;
		for (size_t i = 0; i < strings_count - 1; i++)//до (strings_count - 1) тк метка не должна быть последней строкой в коде
		{
			curr_str = file_redear_.get_line(i);
			auto colon_pos = curr_str.find(':');
			if (colon_pos == std::string::npos) {
				continue;
			}
			int reference_key;
			auto argument = curr_str.substr(0, colon_pos);
			try {
				reference_key = std::stoi(argument, nullptr);
			}
			catch (std::exception& ex) {
				crush_programm("Error in Assembler::define_all_references(): failed reference value\n", ex);
			}
			auto references_count = references_.size();
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
		exit(1);
	}

	void Assembler::crush_programm(std::string msg) {
		crush_programm(msg.c_str());
	}

	void Assembler::put_double_bytes_to_code(double val) {
		uchar argument_bytes[sizeof(double)];
		memcpy(argument_bytes, &val, sizeof(double));
		for (uchar byte : argument_bytes) {
			code_.push_back(byte);
		}
	}

	void Assembler::put_int_bytes_to_code(int val) {
		uchar argument_bytes[sizeof(int)];
		memcpy(argument_bytes, &val, sizeof(int));
		for (uchar byte : argument_bytes) {
			code_.push_back(byte);
		}
	}

	uchar Assembler::get_register_code(std::string reg_name) {
		for (auto valid_reg : valid_registers) {
			if (reg_name == valid_reg.name_) {
				return valid_reg.code_;
			}
		}
		throw std::invalid_argument("Illegal register name");
	}

	void Assembler::generate_code_for_jmp_commands(std::string argument, Assembler::JUMP_COMANDS cmd_type, std::string line_number_str) {
		auto colon_pos = argument.find(':');
		if (colon_pos == std::string::npos) {
			crush_programm(std::string("Error in Assembler::generate_code_for_single_line(std::string command_line): \
								illegal JMP comand\nLine number: ") + line_number_str);
		}
		auto flag_to_call = argument.substr(colon_pos + 1, std::string::npos);
		int flag, adress;
		try {
			flag = std::stoi(flag_to_call);
		}
		catch (...) {
			crush_programm(std::string("Error in Assembler::generate_code_for_single_line(std::string command_line): illegal flag to call.\nError line: ")
				+ line_number_str + std::string("\n"));
		}
		adress = references_[flag];
		code_.push_back((uchar)cmd_type);
		put_int_bytes_to_code(adress);
	}

}
