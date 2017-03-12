#include<iostream>
#include"Integer_Iterator.h"
#include"Dynamic_Array.h"

int main()
{
	Dynamic_Array arr(10), arr2(5);
	int filler = 1;
	for (Array_Iterator<int> it = arr.begin(); it != arr.end(); ++it)
	{
		*it = filler * filler;
		++filler;
	}
	/*int i = 0;
	for (Array_Iterator<int> it = arr.begin(); it != arr.end(); ++it)
	{
		std::cout << "arr[" << i << "] = " << *it << std::endl;
		++i;
	}*/

	arr2 = arr;

	std::cout << "\n\nArray after assigning:\n";
	int i = 0;
	for (Array_Iterator<int> it = arr2.begin(); it != arr2.end(); ++it, ++i)
	{
		std::cout << "arr2[" << i << "] = " << *it << std::endl;
	}
	getchar();
	return 0;
}