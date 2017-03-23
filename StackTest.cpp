#include<iostream>
#include<cassert>
#include<cmath>

#include"Stack.hpp"
#include"gtest\gtest.h"


TEST(Stack, Push_one_element)
{

	//GIVEN: s - стэк даблов
	ava::Stack<double> s;

	//WHEN: кладём в стэк s элемент element_to_push и достаём последний элемент стэка - poped_element
	double element_to_push = 5.0;
	s.push(element_to_push);
	double poped_element = s.pop();

	//THEN: элементо, который мы полоижили в стэк и достали из него должны совпадать
	ASSERT_TRUE(element_to_push == poped_element);
}

TEST(Stack, Over_poping)
{
	//GIVEN: s - стэк интов
	ava::Stack<int> s;

	//WHEN: положили в стэк 5 значений, затем вытащили 5 значений и пытаемся ещё раз вытащить
	for (size_t i = 0; i < 5; i++) {
		s.push(i);
	}
	for (size_t i = 0; i < 5; i++) {
		s.pop();
	}
	try {
		int el = s.pop();
	}
	//THEN: вывод на консоль сообщение об обработанном исключении
	catch (std::length_error& ex) {
		std::cout << ex.what() << std::endl;
	}
}

class Stack_For_Equality_Cheking : public testing::Test
{
public:
	Stack_For_Equality_Cheking()
	{
		init_stack = new ava::Stack<int>();
		assigned_stack = new ava::Stack<int>();

		init_stack->push(element_to_push);

		copy_stack = new ava::Stack<int>(*init_stack);
		*assigned_stack = *init_stack;
	}

protected:
	const int element_to_push = 12;
	ava::Stack<int> *init_stack, *copy_stack, *assigned_stack;
};

//! Нужно использовать TEST_F макрос чтобы пользоваться объектом Stack_For_Equality_Cheking
TEST_F(Stack_For_Equality_Cheking, Check_eqaulity_of_capacities_of_equal_stacks)
{
	//GIVEN: init_stack - исходный стэк c одним элементом; copy_stack - скопированный стэк (результат копи-конструктора: Stack copy_stack(init_stack));
	// assigned_stack - присвоеный стэк (результат перегруженного оператора присваивания: assigned_stack = init_stack)
	// см. класс Stack_For_Equality_Cheking

	//WHEN: init_cap - вместимость исходного (начального) стэка; copy_cap - вместимость скопированного стэка; assigned_cap - вместимость присвоенного стэка
	size_t init_cap = init_stack->getCapacity(),
		copy_cap = copy_stack->getCapacity(),
		assigned_cap = assigned_stack->getCapacity();

	//THEN: вместимости скопированного и присвоенного стэка должны совпадать с вместимостью исходного стэка
	ASSERT_TRUE(init_cap == copy_cap);
	ASSERT_TRUE(init_cap == assigned_cap);
}

TEST_F(Stack_For_Equality_Cheking, Check_eqaulity_of_sizes_of_equal_stacks)
{
	//GIVEN: init_stack - исходный стэк c одним элементом; copy_stack - скопированный стэк (результат копи-конструктора: Stack copy_stack(init_stack));
	// assigned_stack - присвоеный стэк (результат перегруженного оператора присваивания: assigned_stack = init_stack)
	// см. класс Stack_For_Equality_Cheking

	//WHEN: init_size - размер исходного (начального) стэка; copy_size - размер скопированного стэка; assigned_size - размер присвоенного стэка
	size_t init_size = init_stack->getSize(),
		copy_size = copy_stack->getSize(),
		assigned_size = assigned_stack->getSize();

	//THEN: размеры скопированного и присвоенного стэка должны совпадать с размером исходного стэка
	ASSERT_TRUE(init_size == copy_size);
	ASSERT_TRUE(init_size == assigned_size);
}

TEST_F(Stack_For_Equality_Cheking, Check_eqaulity_of_elements_of_equal_stacks)
{
	//GIVEN: element_in_oroginal_stack - элемент, который лежит в исходном стэке (откуда бралась копия и делалось присваивание)
	int element_in_oroginal_stack = element_to_push;

	//WHEN: достаём элемент из копи-стэка - element_from_copy,
	//и элемент из присвоенного стэка (результат перегруженной операции присваивания) - element_from_assigned
	int element_from_copy = copy_stack->pop(),
		element_from_assigned = assigned_stack->pop();

	//THEN: проверяем равны ли элемент из копи-стэка (element_from_copy) и из присвоенного стэка (element_from_assigned) элементу, который лежит в исходном стэке
	bool is_copy_element_equal_to_init = (element_from_copy == element_in_oroginal_stack);
	bool is_assigned_element_equal_to_init = (element_from_assigned == element_in_oroginal_stack);
	ASSERT_TRUE(is_copy_element_equal_to_init);
	ASSERT_TRUE(is_assigned_element_equal_to_init);
}

TEST(Stack, Top_test)
{
	//GIVEN: s - интовский стэк, to_push1, to_push2 - значения, которые кладутся в стэк s
	ava::Stack<int> s;
	int to_push1 = 10, to_push2 = 11;

	//WHEN: кладём в стэк сперва to_push1, а затем to_push2. top_element - последний элемент стэка
	s.push(to_push1);
	s.push(to_push2);
	int top_element = s.top();

	//THEN: проверяем, что последний элемент в стэке равен последнему положенному элементу
	ASSERT_TRUE(top_element == to_push2);
}

TEST(Stack, Top_with_empty_stack)
{
	//GIVEN: s - стэк интов
	ava::Stack<int> s;

	//WHEN: попытка получить верхний элемент пустого стэка
	try {
		int element = s.top();
	}
	//THEN: Перехват сгенирированного исключения
	catch (std::length_error& ex) {
		std::cout << ex.what() << std::endl;
	}
}

TEST(Stack, Overflow_memory)
{
	//GIVE: s - стэк интов
	ava::Stack<int> s;
	//WHEN: создаём огромный стэк
	try {
		s = ava::Stack<int>(SIZE_MAX);
	}
	//THEN: перехват сгенирированного исключения
	catch (std::bad_alloc& ba) {
		std::cout << "There are not memory for such big stack. Stack with default capacity will create\n" << ba.what() << std::endl;
		s = ava::Stack<int>();
	}
}


int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
}