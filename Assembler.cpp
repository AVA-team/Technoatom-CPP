#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Assembler.h"

namespace ava {

	Assembler::Assembler(std::string file_name) :
		source_filename_(file_name),
		destination_filename_(std::string("assembly_") + file_name)
	{}

	Assembler::~Assembler()
	{
		if (fin_.is_open()) 
		{
			fin_.close();
		}
		if (fout_.is_open())
		{
			fout_.close();
		}
	}

	void Assembler::compile()
	{
		fin_.open(source_filename_);
		if (!fin_.is_open())
		{
			throw std::exception("Error with source file open!");
		}
		define_all_references();
		/*
		for (auto it = references_.cbegin(); it != references_.cend(); ++it)
		{
			std::cout << it->first << " " << it->second <<  "\n";
		}
		*/
		fin_.clear();
		fin_.seekg(0, std::ios::beg);
		fout_.open(destination_filename_);
		if (!fout_.is_open())
		{
			throw std::exception("Error with destination file open!");
		}
		parse_in_output();
		fin_.close();
		fout_.close();
	}

	void Assembler::define_all_references()
	{
		std::string line;
		int operand_num = 0;
		while (getline(fin_, line))
		{
			std::string first_operand, second_operand;
			std::stringstream iss(line);
			if (std::getline(iss, first_operand, ' '))
			{
				if (first_operand.at(0) == symbol_of_reference_)
				{
					int ref_num = std::stoi(first_operand.substr(1));
					references_.emplace(ref_num, operand_num);
				}
				else
				{
					++operand_num;
					if (std::getline(iss, second_operand, ' '))
					{
						++operand_num;
					}
				}
			}
			else {
				throw std::exception("Error with reading file!");
			}
		}
	}

	void Assembler::parse_in_output()
	{
		std::string line;
		int operand_num = 0;
		while (getline(fin_, line))
		{
			std::string first_operand, second_operand;
			std::stringstream iss(line);
			if (std::getline(iss, first_operand, ' '))
			{
				if (first_operand.at(0) == symbol_of_reference_)
				{
					continue;
				}
				else {
					auto command = availible_commands.begin();
					for (command; command < availible_commands.end(); command++)
					{
						if (first_operand == (*command).name_)
						{
							Command_code code = (*command).code_;
							fout_ << code << " ";
							if ((*command).argument_existing_)
							{
								if (std::getline(iss, second_operand, ' '))
								{
									if (in_jmps_commands(code))
									{
										int ref_num = std::stoi(second_operand);
										fout_ << references_.at(ref_num) << " ";
									}
									else
									{
										fout_ << second_operand << " ";
									}
								}
								else
								{
									throw std::exception("Error: command need argument!");
								}
							}
							break;
						}
					}
					if (command == availible_commands.end())
					{
						throw std::exception("Error: not availible command!");
					}
				}
			}
			else {
				throw std::exception("Error with reading file!");
			}
		}
	}

	bool Assembler::in_jmps_commands(Command_code code)
	{
		return (code == CALL) ||
			   (code == JMP)  ||
			   (code == JMPE) ||
			   (code == JMPA) ||
			   (code == JMPAE)||
			   (code == JMPB) ||
			   (code == JMPBE)||
			   (code == JMPNE);
	}

}

