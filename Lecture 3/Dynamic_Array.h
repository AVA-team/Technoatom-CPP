#pragma once
#include<cstdlib>
#include"Integer_Iterator.h"

class Dynamic_Array
{
public:
	Dynamic_Array(std::size_t size);
	Dynamic_Array(const Dynamic_Array& that);
	~Dynamic_Array();
	const Dynamic_Array& operator=(const Dynamic_Array& that);
	void* operator new(std::size_t size, void* adress);
	Array_Iterator<int> begin();
	Array_Iterator<int> end();
	std::size_t size() { return size_; }

private:
	std::size_t size_;
	int* data_;
};

