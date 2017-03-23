#include<iostream>
#include<cassert>
#include<cmath>

#include"Stack.hpp"
#include"gtest\gtest.h"


TEST(Stack, Push_one_element)
{

	//GIVEN: s - ���� ������
	ava::Stack<double> s;

	//WHEN: ����� � ���� s ������� element_to_push � ������ ��������� ������� ����� - poped_element
	double element_to_push = 5.0;
	s.push(element_to_push);
	double poped_element = s.pop();

	//THEN: ��������, ������� �� ��������� � ���� � ������� �� ���� ������ ���������
	ASSERT_TRUE(element_to_push == poped_element);
}

TEST(Stack, Over_poping)
{
	//GIVEN: s - ���� �����
	ava::Stack<int> s;

	//WHEN: �������� � ���� 5 ��������, ����� �������� 5 �������� � �������� ��� ��� ��������
	for (size_t i = 0; i < 5; i++) {
		s.push(i);
	}
	for (size_t i = 0; i < 5; i++) {
		s.pop();
	}
	try {
		int el = s.pop();
	}
	//THEN: ����� �� ������� ��������� �� ������������ ����������
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

//! ����� ������������ TEST_F ������ ����� ������������ �������� Stack_For_Equality_Cheking
TEST_F(Stack_For_Equality_Cheking, Check_eqaulity_of_capacities_of_equal_stacks)
{
	//GIVEN: init_stack - �������� ���� c ����� ���������; copy_stack - ������������� ���� (��������� ����-������������: Stack copy_stack(init_stack));
	// assigned_stack - ���������� ���� (��������� �������������� ��������� ������������: assigned_stack = init_stack)
	// ��. ����� Stack_For_Equality_Cheking

	//WHEN: init_cap - ����������� ��������� (����������) �����; copy_cap - ����������� �������������� �����; assigned_cap - ����������� ������������ �����
	size_t init_cap = init_stack->getCapacity(),
		copy_cap = copy_stack->getCapacity(),
		assigned_cap = assigned_stack->getCapacity();

	//THEN: ����������� �������������� � ������������ ����� ������ ��������� � ������������ ��������� �����
	ASSERT_TRUE(init_cap == copy_cap);
	ASSERT_TRUE(init_cap == assigned_cap);
}

TEST_F(Stack_For_Equality_Cheking, Check_eqaulity_of_sizes_of_equal_stacks)
{
	//GIVEN: init_stack - �������� ���� c ����� ���������; copy_stack - ������������� ���� (��������� ����-������������: Stack copy_stack(init_stack));
	// assigned_stack - ���������� ���� (��������� �������������� ��������� ������������: assigned_stack = init_stack)
	// ��. ����� Stack_For_Equality_Cheking

	//WHEN: init_size - ������ ��������� (����������) �����; copy_size - ������ �������������� �����; assigned_size - ������ ������������ �����
	size_t init_size = init_stack->getSize(),
		copy_size = copy_stack->getSize(),
		assigned_size = assigned_stack->getSize();

	//THEN: ������� �������������� � ������������ ����� ������ ��������� � �������� ��������� �����
	ASSERT_TRUE(init_size == copy_size);
	ASSERT_TRUE(init_size == assigned_size);
}

TEST_F(Stack_For_Equality_Cheking, Check_eqaulity_of_elements_of_equal_stacks)
{
	//GIVEN: element_in_oroginal_stack - �������, ������� ����� � �������� ����� (������ ������� ����� � �������� ������������)
	int element_in_oroginal_stack = element_to_push;

	//WHEN: ������ ������� �� ����-����� - element_from_copy,
	//� ������� �� ������������ ����� (��������� ������������� �������� ������������) - element_from_assigned
	int element_from_copy = copy_stack->pop(),
		element_from_assigned = assigned_stack->pop();

	//THEN: ��������� ����� �� ������� �� ����-����� (element_from_copy) � �� ������������ ����� (element_from_assigned) ��������, ������� ����� � �������� �����
	bool is_copy_element_equal_to_init = (element_from_copy == element_in_oroginal_stack);
	bool is_assigned_element_equal_to_init = (element_from_assigned == element_in_oroginal_stack);
	ASSERT_TRUE(is_copy_element_equal_to_init);
	ASSERT_TRUE(is_assigned_element_equal_to_init);
}

TEST(Stack, Top_test)
{
	//GIVEN: s - ��������� ����, to_push1, to_push2 - ��������, ������� �������� � ���� s
	ava::Stack<int> s;
	int to_push1 = 10, to_push2 = 11;

	//WHEN: ����� � ���� ������ to_push1, � ����� to_push2. top_element - ��������� ������� �����
	s.push(to_push1);
	s.push(to_push2);
	int top_element = s.top();

	//THEN: ���������, ��� ��������� ������� � ����� ����� ���������� ����������� ��������
	ASSERT_TRUE(top_element == to_push2);
}

TEST(Stack, Top_with_empty_stack)
{
	//GIVEN: s - ���� �����
	ava::Stack<int> s;

	//WHEN: ������� �������� ������� ������� ������� �����
	try {
		int element = s.top();
	}
	//THEN: �������� ���������������� ����������
	catch (std::length_error& ex) {
		std::cout << ex.what() << std::endl;
	}
}

TEST(Stack, Overflow_memory)
{
	//GIVE: s - ���� �����
	ava::Stack<int> s;
	//WHEN: ������ �������� ����
	try {
		s = ava::Stack<int>(SIZE_MAX);
	}
	//THEN: �������� ���������������� ����������
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