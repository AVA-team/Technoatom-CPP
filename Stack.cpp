#include<string>
#include<cassert>
#include<fstream>
#include<iostream>
#include<new>
//#include<stdlib.h>
#include"Stack.h"

using namespace AVA;

#define ASSERT_OK()					\
if (!isStackOk())					\
{									\
	dump();							\
	assert(!"Stack object is OK");	\
}									\

Stack::Stack() : data_(NULL), size_(0), capacity_(Stack::STACK_DEFAULT_CAPASITY)
{
	try
	{
		data_ = new Stack_Content_Type[capacity_];
	}
	catch (std::bad_alloc& ba)
	{
		std::cerr << "\n\nFailed attempt to allocate dynamic memory for the stack data. Exception occured in Stack::Stack(size_t capacity)\n" << ba.what() << std::endl;
		throw ba;
	}
}


Stack::Stack(size_t capacity) : data_(NULL), size_(0), capacity_(capacity)
{
	try
	{
		data_ = new Stack_Content_Type[capacity_];
	}
	catch (std::bad_alloc& ba)
	{
		std::cerr << "\n\nFailed attempt to allocate dynamic memory for the stack data. Exception occured in Stack::Stack(size_t capacity)\n" << ba.what() << std::endl;
		throw ba;
	}
}


Stack::Stack(const Stack& other) : data_(NULL), size_(other.size_), capacity_(other.capacity_)
{
	deepCopy(other);
}


const Stack& Stack::operator=(const Stack& other)
{
	Stack victim(other);
	swap(*this, victim);
	return (*this);
}


Stack::~Stack()
{
	capacity_ = 0;//Destroying object to avoid its using
	size_ = capacity_ + 1; //Destroying object to avoid its using
	delete[] data_;
}



void Stack::deepCopy(const Stack& other)
{
	data_ = new Stack_Content_Type[other.capacity_];
	size_t size = other.size_;

	for (size_t i = 0; i < size; i++)
	{
		data_[i] = other.data_[i];
	}
}



bool Stack::push(Stack_Content_Type element_to_push)
{

	if (size_ >= capacity_)
	{
		ASSERT_OK(); //Entry verification
		return false;
	}
	else
	{
		ASSERT_OK();
		data_[size_++] = element_to_push;
		return true;
	}
}


Stack_Content_Type Stack::pop()
{

	if (size_ > 0)
	{
		ASSERT_OK();
		return data_[--size_];
	}
	else
	{
		throw Stack::EmptyStackException("There is no elements in the stack. Failed invocation Stack::pop()");
	}
}


Stack_Content_Type Stack::top() const
{
	if (size_ > 0)
	{
		ASSERT_OK();
		return data_[size_ - 1];
	}
	else
	{
		throw Stack::EmptyStackException("There is no elements in the stack. Failed invocation Stack::top()");
	}
}


bool Stack::isEmpty() const
{
	return size_ == 0;
}


size_t Stack::getSize() const
{
	return size_;
}


size_t Stack::getCapacity() const
{
	return capacity_;
}


bool Stack::isStackOk() const
{
	return size_ <= capacity_;
}

void Stack::dump() const
{

	std::string dumpContent = (size_ <= capacity_) ? "Stack (OK)\n\t{\n" : "Stack (ERROR)\n\t{\n";

	dumpContent += "\tCapacity = " + std::to_string(capacity_) + "\n" + "\tSize = " + std::to_string(size_) + "\n\n\t\tdata[" + std::to_string(capacity_) + "]:\n\t\t{\n";

	for (size_t i = 0; i < capacity_; i++)
	{
		if (i < size_)
		{
			dumpContent += "   \t*\tElement ¹ " + std::to_string(i) + ")\t" + std::to_string(data_[i]) + "\n";
		}
		else
		{
			dumpContent += "\t\tElement ¹ " + std::to_string(i) + ")\t" + std::to_string(data_[i]) + " (TRASH)\n";
		}
	}

	dumpContent += "\t\t}\n\t}\n";

	std::ofstream fout;

	fout.open("Stack_Dump.txt");//open file Stack_Dump.txt if it exist or create new file

	fout << __DATE__ << std::endl << __TIME__ << "\n\n\n" << dumpContent;

	fout.close();

	std::cout << "Stack dump file was saved in current directory. See Stack_Dump.txt\n";
}
