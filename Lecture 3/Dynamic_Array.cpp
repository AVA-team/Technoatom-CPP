#include<iostream>
#include "Dynamic_Array.h"



Dynamic_Array::Dynamic_Array(std::size_t size) :size_(size), data_(new int[size_])
{

}

Dynamic_Array::Dynamic_Array(const Dynamic_Array& that) : size_(that.size_), data_(nullptr)
{
	data_ = new int[size_];

	for (size_t i = 0; i < size_; i++)
	{
		data_[i] = that.data_[i];
	}
}


Dynamic_Array::~Dynamic_Array()
{
	delete[] data_;
	size_ = 0;
}

void* Dynamic_Array::operator new(std::size_t size, void* adress)
{
	std::cout << "Overwriten new operator. Returning adress: 0x" << adress << std::endl;
	return adress;
}

const Dynamic_Array& Dynamic_Array::operator=(const Dynamic_Array& that)
{
	if (&that != this)
	{
		std::cout << "Overwritten operator=. Adress of destroying object: 0x" << this << std::endl;
		this->~Dynamic_Array();
		new(this)Dynamic_Array(that);
	}

	return *this;
}

Array_Iterator<int> Dynamic_Array::begin()
{
	return Array_Iterator<int>(data_);
}

Array_Iterator<int> Dynamic_Array::end()
{
	return Array_Iterator<int>(data_ + size_);
}
