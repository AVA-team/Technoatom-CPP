#include<iostream>

void print(char* str) {
	std::cout << str << std::endl;
}

template<class T, class...Args>
void print(char* str, T val, Args...args) {
	while (*str)
		if (*str != '#') std::cout << *str++;
		else {
			std::cout << val;
			print(str + 1, args...);
			break;
		}
}

int main(int argc, char** argv)
{
	print("Hello! My name is #. My age is #. My salary is #\n", "Ahmed", 23, 6.7);

	system("pause");
	return 0;
}