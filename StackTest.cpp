#include<iostream>
#include<cassert>
#include<cmath>

#include"Stack.h"
#include"gtest\gtest.h"

using namespace AVA;
using namespace std;


//----------------------------------------------------------
//! Macros to orgonize test code in the main function
//! @param what - an object to test
//! @param caseToTest  - what test to run
//---------------------------------------------------------

//#define TEST( what, caseToTest ) 

//#define ASSERT_TRUE(condition) \
//if(!(condition))				 \
//{							 \
//	assert(!#condition);     \
//}							 \


Stack* function_returning_local_stack_pointer()
{
	Stack localStack;

	localStack.push(10);

	return &localStack;
}

TEST(Stack, Push_one_element)
{
	Stack s;

	StackContentType elementToPush = 5.0;

	s.push(elementToPush);
	StackContentType popedElement = s.pop();

	ASSERT_TRUE(elementToPush == popedElement);
}

TEST(Stack, Can_not_push_more)
{
	Stack s;

	size_t capacity = s.getCapacity();

	for (size_t i = 0; i < capacity; i++)
	{
		s.push(i);
	}

	StackContentType valueWillNotBePushed = 12.1;

	ASSERT_TRUE(s.push(valueWillNotBePushed) == false);
}

TEST(Stack, Over_poping)
{
	Stack s;

	for (size_t i = 0; i < 5; i++)
	{
		s.push(i);
	}

	for (size_t i = 0; i < 5; i++)
	{
		s.pop();
	}

	try
	{
		StackContentType el = s.pop();
	}
	catch (Stack::EmptyStackException& ex)
	{
		std::cout << "\nEmptyStackException catched in Stack::pop()\n" << ex.what() << std::endl;
	}
}

class Stack_For_Equality_Cheking : public testing::Test
{
public:
	Stack_For_Equality_Cheking()
	{
		init_stack = new Stack();
		assigned_stack = new Stack();

		init_stack->push(first_element_to_push);
		init_stack->push(second_element_to_push);
		init_stack->push(third_element_to_push);

		copy_stack = new Stack(*init_stack);
		*assigned_stack = *init_stack;
	}

protected:
	const StackContentType first_element_to_push = 12, second_element_to_push = 13, third_element_to_push = 14;
	Stack *init_stack, *copy_stack, *assigned_stack;
};

//! We need specify TEST_F macro to use Stack_For_Equality_Cheking object here
TEST_F(Stack_For_Equality_Cheking, Check_eqaulity_of_capacities_of_equal_stacks)
{
	size_t init_cap = init_stack->getCapacity(),
		copy_cap = copy_stack->getCapacity(),
		assigned_cap = assigned_stack->getCapacity();

	ASSERT_TRUE(init_cap == copy_cap);
	ASSERT_TRUE(init_cap == assigned_cap);
}

TEST_F(Stack_For_Equality_Cheking, Check_eqaulity_of_sizes_of_equal_stacks)
{
	size_t init_size = init_stack->getSize(),
		copy_size = copy_stack->getSize(),
		assigned_size = assigned_stack->getSize();

	ASSERT_TRUE(init_size == copy_size);
	ASSERT_TRUE(init_size == assigned_size);
}

TEST_F(Stack_For_Equality_Cheking, Check_eqaulity_of_elements_of_equal_stacks)
{
	size_t init_size = init_stack->getSize(),
		copy_size = copy_stack->getSize(),
		assigned_size = assigned_stack->getSize();

	StackContentType third_element_from_copy = copy_stack->pop(),
		second_element_from_copy = copy_stack->pop(),
		first_element_from_copy = copy_stack->pop(),
		third_element_from_assigned = assigned_stack->pop(),
		second_element_from_assigned = assigned_stack->pop(),
		first_element_from_assigned = assigned_stack->pop();

	bool is_copy_elements_equal_to_init = (third_element_from_copy == third_element_to_push) && (second_element_from_copy == second_element_to_push)
		&& (first_element_from_copy == first_element_to_push);

	bool is_assigned_elements_equal_to_init = (third_element_from_assigned == third_element_to_push) && (second_element_from_assigned == second_element_to_push)
		&& (first_element_from_assigned == first_element_to_push);

	ASSERT_TRUE(is_copy_elements_equal_to_init);
	ASSERT_TRUE(is_assigned_elements_equal_to_init);
}

TEST(Stack, Top_method_test)
{
	Stack s;

	StackContentType toPush = 10;
	s.push(toPush);
	toPush = 11;
	s.push(toPush);

	StackContentType topElement = s.top();

	ASSERT_TRUE(topElement == toPush);
}

TEST(Stack, Top_method_with_empty_stack)
{
	Stack s;

	try
	{
		StackContentType element = s.top();
	}
	catch (Stack::EmptyStackException& ex)
	{
		std::cout << "\nEmptyStackException catched in Stack::top()\n" << ex.what() << std::endl;
	}
}

TEST(Stack, Overflow_memory)
{
	Stack overflow_memory_stack;

	try
	{
		overflow_memory_stack = Stack(SIZE_MAX);
	}
	catch (std::bad_alloc& ba)
	{
		std::cout << "There are not memory for such big stack. Stack with default capacity will create\n" << ba.what() << std::endl;
		overflow_memory_stack = Stack();
	}
}

TEST(Stack, Using_stack_after_its_destroying)
{
	Stack* s = function_returning_local_stack_pointer();//destructor set capacity_ = 0 and size_ = 1. Object was destroying

	StackContentType elementToPush = 15;

	s->push(elementToPush);//in push method both size and capacity = 3435973836. WTF!!??
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
}