#include "processor.h"
#include "command.h"
#include <sstream>
#include <iostream>


ava::Processor::Processor()
{}

ava::Processor::Processor(const std::string & file_name) :
	executable_file_name_(file_name)
{}

ava::Processor::~Processor()
{
	close_file_streams();
}

void ava::Processor::executable_file_bind(const std::string & file_name)
{
	close_file_streams();
	executable_file_name_ = file_name;
}

void ava::Processor::process()
{
	load_code();
	step_ = 0;
	std::size_t code_size = code_.size();
	while (code_.at(step_) != END && step_ < code_size)
	{
		switch (code_[step_])
		{
		case PUSH:
			push(code_[step_ + 1]);
			step_ += 2;
			break;
		case PUSH_REG:
			push_reg(code_[step_ + 1]);
			step_ += 2;
			break;
		case POP:
			pop(code_[step_ + 1]);
			step_ += 2;
			break;
		case ADD:
			add();
			++step_;
			break;
		case DIV:
			div();
			++step_;
			break;
		case MUL:
			mul();
			++step_;
			break;
		case RET:
			ret();
			break;
		case CALL:
			call();
			break;
		case JMP:
			jmp(code_[step_ + 1]);
			break;
		case JMPE:
			conditional_jmp_process(std::equal_to<int>());
			break;
		case JMPA:
			conditional_jmp_process(std::greater<int>());
			break;
		case JMPAE:
			conditional_jmp_process(std::greater_equal<int>());
			break;
		case JMPB:
			conditional_jmp_process(std::less<int>());
			break;
		case JMPBE:
			conditional_jmp_process(std::less_equal<int>());
			break;
		case JMPNE:
			conditional_jmp_process(std::not_equal_to<int>());
			break;
		default:
			throw std::exception("Error: not availible command!");
			break;
		}
	}
	std::cout << "Programm sucessfuly executed\n";
}

void ava::Processor::show_state() const
{
	std::cout << "Registers values:" << std::endl;
	for (auto & reg: registers_)
	{
		std::cout << reg << " ";
	}
	std::cout << std::endl << "Data stack values (from top to bot):" << std::endl;
	auto tmp_data_stack = data_stack_;
	while (!tmp_data_stack.empty())
	{
		std::cout << tmp_data_stack.top() << " ";
		tmp_data_stack.pop();
	}
	std::cout << std::endl;
}

void ava::Processor::set_data_stack(const std::vector<int> & data)
{
	for (auto rit = data.crbegin(); rit != data.crend(); ++rit)
	{
		data_stack_.push(*rit);
	}
}

void ava::Processor::close_file_streams()
{
	if (fin_.is_open())
	{
		fin_.close();
	}
}

void ava::Processor::load_code()
{
	fin_.open(executable_file_name_);
	if (!fin_.is_open())
	{
		throw std::exception("Error with source file open!");
	}
	int code;
	while (fin_ >> code)
	{
		code_.push_back(code);
	}
	close_file_streams();
}

void ava::Processor::push(int value)
{
	data_stack_.push(value);
}

void ava::Processor::push_reg(std::size_t reg_ind)
{
	data_stack_.push(registers_.at(reg_ind));
}

void ava::Processor::pop(std::size_t reg_ind)
{
	registers_.at(reg_ind) = data_stack_.top();
	data_stack_.pop();
}

void ava::Processor::add()
{
	int result = data_stack_.top();
	data_stack_.pop();
	result += data_stack_.top();
	data_stack_.pop();
	data_stack_.push(result);
}

void ava::Processor::div()
{
	int result = data_stack_.top();
	data_stack_.pop();
	result = data_stack_.top() / result;
	data_stack_.pop();
	data_stack_.push(result);
}

void ava::Processor::mul()
{
	int result = data_stack_.top();
	data_stack_.pop();
	result *= data_stack_.top();
	data_stack_.pop();
	data_stack_.push(result);
}

void ava::Processor::ret()
{
	std::size_t next_step = call_stack_.top();
	call_stack_.pop();
	step_ = next_step;
}

void ava::Processor::call()
{
	call_stack_.push(step_ + 2);
	jmp(code_[step_ + 1]);
}

void ava::Processor::jmp(std::size_t command_ind)
{
	step_ = command_ind;
}

void ava::Processor::conditional_jmp_process(std::function<bool(int, int)> comporator)
{
	int second_compared_num = data_stack_.top(),
		first_compared_num;
	data_stack_.pop();
	first_compared_num = data_stack_.top();
	data_stack_.pop();
	if (comporator(first_compared_num, second_compared_num))
	{
		jmp(code_[step_ + 1]);
	}
	else
	{
		step_ += 2;
	}
}
