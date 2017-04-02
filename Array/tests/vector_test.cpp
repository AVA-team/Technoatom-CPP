#include <iostream>
#include "gtest\gtest.h"
#include "../implementation/vector.hpp"

TEST(Vector, Constructor_with_capacity)
{
	// GIVEN:
	//
	// vec_default - ������ ��������� ������������� �� ���������
	// vec - ������ ��������� �������������, ����������� �������� ����������� (capacity)
	// init_capacity - ����������� ������� vec
	ava::Vector<int> vec_default;
	const size_t init_capacity = 15;
	ava::Vector<int> vec(init_capacity);

	// WHEN:
	//
	// vec_default_capacity - ����������� ������� vec_default
	// vec_default_size - ������ ������� vec_default
	std::size_t vec_default_capacity = vec_default.capacity();
	std::size_t vec_default_size = vec_default.size();

	// THEN:
	//
	// ����������� � ������ vec_default ������ ��������� 10 � 0 ��������������
	// ����������� � ������ vec ������ ��������� 15 � 0 ��������������
	ASSERT_TRUE(vec_default_capacity == ava::default_capacity);
	ASSERT_TRUE(vec_default_size == 0);
	ASSERT_TRUE(vec.capacity() == init_capacity);
	ASSERT_TRUE(vec.size() == 0);
}

TEST(Vector, Constructor_with_size_and_value)
{
	// GIVEN:
	//
	// init_size - ������ ��������� �������
	// init_value - ��������, ������� ���������� �������� ��������� �����
	const size_t init_size = 2;
	const int init_value = 5;

	// WHEN:
	//
	// vec - ������ ��������� ������������� ������� ��������� ������ ������� � ��������, ������� �� �������� ���� ���������
	ava::Vector<int> vec(init_size, init_value);

	// THEN:
	//
	// ������ ������� ������ ��������� init_size
	// �������� ������� ������ ��������� init_value
	ASSERT_TRUE(vec.size() == init_size);
	ASSERT_TRUE(vec[0] == init_value);
	ASSERT_TRUE(vec[1] == init_value);
}

TEST(Vector, Insert)
{
	// GIVEN:
	//
	// vec - ������ ��������� ������������� �� ��������� (� ������������ 10) � � ����� ���������� (1, 2)
	ava::Vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);

	// WHEN:
	//
	// ��������� ����� ������� �������� ��� ��� �������� ������ 0
	vec.insert(1, 2, 0);

	// THEN:
	//
	// ������ ���������� ������ [1, 0, 0, 2]. ���������
	ASSERT_TRUE( (vec[0] == 1) && (vec[1] == 0) && (vec[2] == 0) && (vec[3] == 2) );
}


TEST(Vector, Push_back)
{
	// GIVEN:
	//
	// vec - ������ ��������� ������������� �� ���������
	// value_to_push - ��������, ������� ����� � ������
	ava::Vector<int> vec;
	int value_to_push = 15;

	// WHEN:
	//
	// ����� value_to_push � ������
	vec.push_back(value_to_push);

	// THEN:
	//
	// ���������, ��� ��������� ������� � ������� ����� ����, ������� �� ���� ��������
	ASSERT_TRUE(vec.back() == value_to_push);
}

TEST(Vector, Push_back_with_auto_incrementing_capacity)
{
	// GIVEN:
	//
	// init_capacity - ��������� ����������� �������
	// vec - ������ ��������� �������������, ������� ��������� �������� ����������� (capacity). vec �������� ��� ��������: 10 � 20
	std::size_t init_capacity = 2;
	ava::Vector<int> vec(init_capacity);
	vec.push_back(10);
	vec.push_back(20);

	// WHEN:
	//
	// ����� ������ ������� 30
	vec.push_back(30);

	// THEN:
	//
	// ���������, ��� ����������� (capacity) ������� �����������
	ASSERT_TRUE(vec.capacity() > init_capacity);
}

class Vector_Object_For_Testing_Single_Vec : public testing::Test
{
public:
	Vector_Object_For_Testing_Single_Vec() :vec_(init_capacity_) {
		vec_[0] = 10;
		vec_[1] = 20;
	}

protected:
	const size_t init_capacity_ = 3;
	const size_t init_size_ = 2;
	ava::Vector<int> vec_;
};

TEST_F(Vector_Object_For_Testing_Single_Vec, Copy_constructor)
{
	// GIVEN:
	//
	// vec_ - ������ ��������������������� � ������ Vector_Object_For_Testing_Single_Vec

	// WHEN:
	// 
	// copy_vec - ������ ������������� �� vec_ (������������� �����������)
	ava::Vector<int> copy_vec(vec_);

	// THEN:
	//
	// �������, ����������� (capacity) � �������� ��������� � �������������� �������� ������ ���������
	ASSERT_TRUE(vec_.size() == copy_vec.size());
	ASSERT_TRUE(vec_.capacity() == copy_vec.capacity());
	ASSERT_TRUE(copy_vec[0] == vec_[0]);
	ASSERT_TRUE(copy_vec[1] == vec_[1]);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Pop_back)
{
	// GIVEN:
	//
	// vec_ - ������ ��������������������� � ������ Vector_Object_For_Testing_Single_Vec
	// init_size_ = 2 - ������ ������� vec_ (����������� � ������ Vector_Object_For_Testing_Single_Vec)

	// WHEN:
	// 
	// ����������� ������� �� �������
	vec_.pop_back();

	// THEN:
	//
	// ������ ������� ������ ����������� �� 1
	ASSERT_TRUE(vec_.size() == (init_size_ - 1));
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Resize_With_Reduction)
{
	// GIVEN:
	//
	// vec_ - ������ ��������������������� � ������ Vector_Object_For_Testing_Single_Vec (vec_[0] = 10, vec_[1] = 20)
	// init_size_ = 2 - ������ ������� vec_ (����������� � ������ Vector_Object_For_Testing_Single_Vec)

	// WHEN:
	//
	// �������� ������ ������� � 2 �� 1 � ���������� ����� ������ ������� � vec_new_size
	vec_.resize(1);
	size_t vec_new_size = vec_.size();

	// THEN:
	//
	// ���������, ��� ������ ������� ���� ����� 1 � ��� ������� ����� 10
	ASSERT_TRUE(vec_new_size == 1);
	ASSERT_TRUE(vec_[0] == 10);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Resize_With_Bigger_Size)
{
	// GIVEN:
	//
	// vec_ - ������ ��������������������� � ������ Vector_Object_For_Testing_Single_Vec (vec_[0] = 10, vec_[1] = 20)
	// init_size_ = 2 - ������ ������� vec_ (����������� � ������ Vector_Object_For_Testing_Single_Vec)
	// value_for_new_elements - �������� ������� ������������� ����� ���������� ��� ��������� ������� � ������� �������
	const int value_for_new_elements = 777;

	// WHEN:
	//
	// �������� ������ ������� � 2 �� 3 � ���������� ����� ������ ������� � vec_new_size
	vec_.resize(3, value_for_new_elements);
	size_t vec_new_size = vec_.size();

	// THEN:
	//
	// ���������, ��� ������ ������� ���� ����� 3 � ��� ������� ����� 10
	ASSERT_TRUE(vec_new_size == 3);
	ASSERT_TRUE(vec_[0] == 10);
	ASSERT_TRUE(vec_[1] == 20);
	ASSERT_TRUE(vec_[2] == value_for_new_elements);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Resize_With_Bigger_Capacity)
{
	// GIVEN:
	//
	// vec_ - ������ ��������������������� � ������ Vector_Object_For_Testing_Single_Vec (vec_[0] = 10, vec_[1] = 20)
	// init_size_ = 2 - ������ ������� vec_ (����������� � ������ Vector_Object_For_Testing_Single_Vec)
	// init_capacity_ - ����������� vec_ (= 3)
	// value_for_new_elements - �������� ������� ������������� ����� ���������� ��� ��������� ������� � ������� �������
	const int value_for_new_elements = 777;

	// WHEN:
	//
	// �������� ������ ������� � 2 �� 3 � ���������� ����� ������ ������� � vec_new_size, � ����� ����������� � vec_new_capacity
	vec_.resize(4, value_for_new_elements);
	size_t vec_new_size = vec_.size(), vec_new_capacity = vec_.capacity();

	// THEN:
	//
	// ���������, ��� ������ ������� ���� ����� 4, ����������� �����������, � ����� �������� ����� value_for_new_elements
	ASSERT_TRUE(vec_new_size == 4);
	ASSERT_TRUE(vec_new_capacity > init_capacity_);
	ASSERT_TRUE(vec_[2] == value_for_new_elements);
	ASSERT_TRUE(vec_[3] == value_for_new_elements);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Assign_With_Count_Less_Than_Capacity_And_Less_Than_Size)
{
	// GIVEN:
	//
	// vec_ - ������ ��������������������� � ������ Vector_Object_For_Testing_Single_Vec (vec_[0] = 10, vec_[1] = 20)
	// init_size_ = 2 - ������ ������� vec_ (����������� � ������ Vector_Object_For_Testing_Single_Vec)
	// init_capacity_ - ����������� vec_ (= 3)
	// value_for_new_elements - �������� ������� ������������� ����� ����������
	const int value_for_new_elements = 777;

	// WHEN:
	//
	// ����������� ������� ����� ����������: ���� �������, ������� ����� value_for_new_elements
	// ���������� ����� ������ ������� � vec_size, � ����� ����������� � vec_capacity
	vec_.assign(1, value_for_new_elements);
	size_t vec_size = vec_.size(), vec_capacity = vec_.capacity();

	// THEN:
	//
	// ���������, ��� ������ ������� ���� ����� 1, ����������� �� ����������, � ������������ ������� ����� 
	ASSERT_TRUE(vec_size == 1);
	ASSERT_TRUE(vec_capacity == init_capacity_);
	ASSERT_TRUE(vec_[0] == value_for_new_elements);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Assign_With_Count_Less_Than_Capacity_And_Bigger_Than_Size)
{
	// GIVEN:
	//
	// vec_ - ������ ��������������������� � ������ Vector_Object_For_Testing_Single_Vec (vec_[0] = 10, vec_[1] = 20)
	// init_size_ = 2 - ������ ������� vec_ (����������� � ������ Vector_Object_For_Testing_Single_Vec)
	// init_capacity_ - ����������� vec_ (= 3)
	// value_for_new_elements - �������� ������� ������������� ����� ����������
	const int value_for_new_elements = 777;

	// WHEN:
	//
	// ����������� ������� ����� ����������: ��� ��������, ������ �� ������� ����� value_for_new_elements
	// ���������� ����� ������ ������� � vec_size, � ����� ����������� � vec_capacity
	vec_.assign(3, value_for_new_elements);
	size_t vec_size = vec_.size(), vec_capacity = vec_.capacity();

	// THEN:
	//
	// ���������, ��� ������ ������� ���� ����� 3, ����������� �� ����������, � ��� �������� �����  value_for_new_elements
	ASSERT_TRUE(vec_size == 3);
	ASSERT_TRUE(vec_capacity == init_capacity_);
	ASSERT_TRUE(vec_[0] == value_for_new_elements);
	ASSERT_TRUE(vec_[1] == value_for_new_elements);
	ASSERT_TRUE(vec_[2] == value_for_new_elements);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Assign_With_Count_Bigger_Than_Capacity_And_Bigger_Than_Size)
{
	// GIVEN:
	//
	// vec_ - ������ ��������������������� � ������ Vector_Object_For_Testing_Single_Vec (vec_[0] = 10, vec_[1] = 20)
	// init_size_ = 2 - ������ ������� vec_ (����������� � ������ Vector_Object_For_Testing_Single_Vec)
	// init_capacity_ - ����������� vec_ (= 3)
	// value_for_new_elements - �������� ������� ������������� ����� ����������
	const int value_for_new_elements = 777;

	// WHEN:
	//
	// ����������� ������� ����� ����������: ������ ��������, ������ �� ������� ����� value_for_new_elements
	// ���������� ����� ������ ������� � vec_size, � ����� ����������� � vec_capacity
	vec_.assign(4, value_for_new_elements);
	size_t vec_size = vec_.size(), vec_capacity = vec_.capacity();

	// THEN:
	//
	// ���������, ��� ������ ������� ���� ����� 4, ����������� �����������, � ������ �������� �����  value_for_new_elements
	ASSERT_TRUE(vec_size == 4);
	ASSERT_TRUE(vec_capacity > init_capacity_);
	ASSERT_TRUE(vec_[0] == value_for_new_elements);
	ASSERT_TRUE(vec_[1] == value_for_new_elements);
	ASSERT_TRUE(vec_[2] == value_for_new_elements);
	ASSERT_TRUE(vec_[3] == value_for_new_elements);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Reserve_with_less_capacity)
{
	// GIVEN:
	//
	// vec_ - ������ ��������������������� � ������ Vector_Object_For_Testing_Single_Vec (vec_[0] = 10, vec_[1] = 20)
	// init_size_ = 2 - ������ ������� vec_ (����������� � ������ Vector_Object_For_Testing_Single_Vec)
	// init_capacity_ - ����������� vec_ (= 3)
	// new_less_capicity - ����� ����������� �������, ������� ������ ��������� (init_capacity_)
	const size_t new_less_capicity = 2;

	// WHEN:
	//
	// ������������� ������ � ���������, � ������� �� �������� ������� new_less_capicity ���������
	vec_.reserve(new_less_capicity);

	// THEN:
	//
	// ���������, ��� ������ ������� � ����������� �� ����������
	ASSERT_TRUE(vec_.size() == init_size_);
	ASSERT_TRUE(vec_.capacity() == init_capacity_);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Reserve_with_bigger_capacity)
{
	// GIVEN:
	//
	// vec_ - ������ ��������������������� � ������ Vector_Object_For_Testing_Single_Vec (vec_[0] = 10, vec_[1] = 20)
	// init_size_ = 2 - ������ ������� vec_ (����������� � ������ Vector_Object_For_Testing_Single_Vec)
	// init_capacity_ - ����������� vec_ (= 3)
	// new_less_capicity - ����� ����������� �������, ������� ������ ��������� (init_capacity_)
	const size_t new_bigger_capicity = 4;

	// WHEN:
	//
	// ������������� ������ � ���������, � ������� �� �������� ������� new_less_capicity ���������
	vec_.reserve(new_bigger_capicity);

	// THEN:
	//
	// ���������, ��� ������ ������� �� ����������, � ����������� �����������
	ASSERT_TRUE(vec_.size() == init_size_);
	ASSERT_TRUE(vec_.capacity() > init_capacity_);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Shrink_to_fit)
{
	// GIVEN:
	//
	// vec_ - ������ ��������������������� � ������ Vector_Object_For_Testing_Single_Vec (vec_[0] = 10, vec_[1] = 20)
	// init_size_ = 2 - ������ ������� vec_ (����������� � ������ Vector_Object_For_Testing_Single_Vec)
	// init_capacity_ - ����������� vec_ (= 3)
	// new_less_capicity - ����� ����������� �������, ������� ������ ��������� (init_capacity_)

	// WHEN:
	//
	// ��������� ����������� ������� �� �������� �������
	vec_.shrink_to_fit();

	// THEN:
	//
	// ���������, ��� ������ ������� �� ���������, � ����������� ����� ����� �������
	ASSERT_TRUE(vec_.size() == init_size_);
	ASSERT_TRUE(vec_.capacity() == init_size_);
}

//! �����, ������� ����������� ������ �������, ������� ������������ � ������ ��������� ������������
class Vector_Objects_For_Cheking_Equality : public testing::Test
{
public:
	Vector_Objects_For_Cheking_Equality() :
		init_vec_(3), first_assigned_vec_(2), second_assigned_vec_(1) {
		init_vec_.push_back(val_1);
		init_vec_.push_back(val_2);
		init_vec_.push_back(val_3);
		second_assigned_vec_ = first_assigned_vec_ = init_vec_;
	}
protected:
	const int val_1 = 10, val_2 = 20, val_3 = 30;
	ava::Vector<int> init_vec_, first_assigned_vec_, second_assigned_vec_;
};

TEST_F(Vector_Objects_For_Cheking_Equality, Check_Capacity_Equality)
{
	// GIVEN:
	// 
	// init_vec_ - �������� ������ � �����������: size = 3, capacity = 3, init_vec_[0] = 10, init_vec_[1] = 20, init_vec_[2] = 30
	// first_assigned_vec_ - ������ ���������� ������ (first_assigned_vec_ = init_vec_)
	// secong_assigned_vec_ - ������ ���������� ������ (secong_assigned_vec_ = first_assigned_vec_ = init_vec_)

	// WHEN
	// 
	// ���������� ����������� ��������� ������� � ���� ����������� �������� � ����������
	// init_cap, first_assigned_cap, second_assigned_cap
	size_t init_cap = init_vec_.capacity(),
		first_assigned_cap = first_assigned_vec_.capacity(),
		second_assigned_cap = second_assigned_vec_.capacity();

	// THEN
	//
	// ���������, ��� ����������� ���� ����������� �������� ����� ����������� ��������� �������
	ASSERT_TRUE(first_assigned_cap == init_cap);
	ASSERT_TRUE(second_assigned_cap == init_cap);
}

TEST_F(Vector_Objects_For_Cheking_Equality, Check_Size_Equality)
{
	// GIVEN:
	// 
	// init_vec_ - �������� ������ � �����������: size = 3, capacity = 3, init_vec_[0] = 10, init_vec_[1] = 20, init_vec_[2] = 30
	// first_assigned_vec_ - ������ ���������� ������ (first_assigned_vec_ = init_vec_)
	// secong_assigned_vec_ - ������ ���������� ������ (secong_assigned_vec_ = first_assigned_vec_ = init_vec_)

	// WHEN
	// 
	// ���������� ������� ��������� ������� � ���� ����������� �������� � ����������
	// init_size, first_assigned_size, second_assigned_size
	size_t init_size = init_vec_.size(),
		first_assigned_size = first_assigned_vec_.size(),
		second_assigned_size = second_assigned_vec_.size();

	// THEN
	//
	// ���������, ��� ������� ���� ����������� �������� ����� ������� ��������� �������
	ASSERT_TRUE(first_assigned_size == init_size);
	ASSERT_TRUE(second_assigned_size == init_size);
}

TEST_F(Vector_Objects_For_Cheking_Equality, Check_Elements_Equality)
{
	// GIVEN:
	// 
	// init_vec_ - �������� ������ � �����������: size = 3, capacity = 3, init_vec_[0] = 10, init_vec_[1] = 20, init_vec_[2] = 30
	// first_assigned_vec_ - ������ ���������� ������ (first_assigned_vec_ = init_vec_)
	// secong_assigned_vec_ - ������ ���������� ������ (secong_assigned_vec_ = first_assigned_vec_ = init_vec_)

	// WHEN
	// 
	// ������ �� ������: ���������� ��� ���� � ������ Vector_Objects_For_Cheking_Equality

	// THEN
	//
	// ���������, ��� �������� ����������� �������� ����� ��������� ��������� �������
	ASSERT_TRUE(first_assigned_vec_[0] == init_vec_[0]);
	ASSERT_TRUE(first_assigned_vec_[1] == init_vec_[1]);
	ASSERT_TRUE(first_assigned_vec_[2] == init_vec_[2]);
	ASSERT_TRUE(second_assigned_vec_[0] == init_vec_[0]);
	ASSERT_TRUE(second_assigned_vec_[1] == init_vec_[1]);
	ASSERT_TRUE(second_assigned_vec_[2] == init_vec_[2]);
}

TEST(Vector, Move_constructor)
{
	// GIVEN
	//
	// vec_size - ������ ������� ���������� �������, ������� ������������������ ������ vec
	// value - �������� �������� ���������������� ��������� ������
	std::size_t vec_size = 2;
	const int value = 777;

	// WHEN
	//
	// ������ ������ � ������� ������������ �����������
	ava::Vector<int> vec(ava::Vector<int>(vec_size, value));

	// THEN
	//
	// ���������, ��� ��������� ������ (������� ��� ����) ������������ ������� vec
	// �������� ��� �� ���� ����� (������, �����������) � ���������
	ASSERT_TRUE(vec.size() == vec_size);
	ASSERT_TRUE(vec.capacity() == vec_size);
	ASSERT_TRUE(vec[0] == value);
	ASSERT_TRUE(vec[1] == value);
}

TEST(Vector, Move_assignment)
{
	// GIVEN:
	// 
	// vec_size - ������ ������� ���������� �������, ������� ������������������ ������ vec
	// value - �������� �������� ���������������� ��������� ������
	// vec - ������, � �������� ��������� �������� ������������ - �����������
	std::size_t vec_size = 2;
	const int value = 777;
	ava::Vector<int> vec;

	// WHEN:
	// 
	// ���������� ������ vec � ������� ��������� ������������-�����������
	vec = ava::Vector<int>(vec_size, value);

	// THEN
	//
	// ���������, ��� ��������� ������ (������� ��� ����) ������������ ������� vec
	// ����������� ��� ���� (������ � �����������)
	ASSERT_TRUE(vec.size() == vec_size);
	ASSERT_TRUE(vec.capacity() == vec_size);
	ASSERT_TRUE(vec[0] == value);
	ASSERT_TRUE(vec[1] == value);
}

TEST(Vector, Initializer_list)
{
	// GIVEN
	//
	// val_1, val_2 - �������� �������� ���������������� ������ vi
	// vi ������, ������� ���������������� � ������� ����� �������������
	const int val_1 = 1, val_2 = 3;
	ava::Vector<int> vi = { val_1, val_2 };

	// WHEN
	//
	// � ���������� el_1, el_2 ���������� ������ � ������ ������� �������
	int el_1 = vi[0], el_2 = vi[1];

	// THEN
	//
	// ���������, ��� �������� ��������� � ���������� ����� �������������
	ASSERT_TRUE(el_1 == val_1);
	ASSERT_TRUE(el_2 == val_2);
}


int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
	return 0;
}
