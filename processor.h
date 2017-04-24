#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <stack>
#include <string>

#ifndef REGISTERS_COUNT
#define REGISTERS_COUNT 10
#endif //REGISTERS_COUNT

namespace ava
{
	class Processor
	{
	public:
		Processor();
		Processor(const std::string & file_name);
		//! delete copy constructor, because fstreams can't be copyd
		Processor(const Processor &) = delete;
		//! delete assigment operator, because fstreams can't be assigment
		Processor & operator= (const Processor &) = delete;
		~Processor();
		void executable_file_bind(const std::string & file_name);
		void process();
		void show_state() const;
		void set_data_stack(const std::vector<int> & data);
	private:
		std::string executable_file_name_;
		std::ifstream fin_;
		std::array<int, REGISTERS_COUNT> registers_;
		std::vector<int> code_;
		std::stack<int> data_stack_;
		std::stack<int> call_stack_;
		void close_file_streams();
		std::size_t step;
		void load_code();
		void push(int value);
		void push_reg(std::size_t reg_ind);
		void pop(std::size_t reg_ind);
		void add();
		void div();
		void mul();
		void ret();
		void call();
		void jmp(std::size_t command_ind);
		void conditional_jmp_process();
	};
}

#endif //PROCESSOR_H_
