#include <iostream>
#include"gtest\gtest.h"
#include "..\Vector.h"

TEST(Vector, Constructor_with_capacity)
{
	ava::Vector<int> vec_with_default_capacity;
	ASSERT_TRUE(vec_with_default_capacity.capacity() == ava::standart_init_capacity);
	ASSERT_TRUE(vec_with_default_capacity.size() == 0);

	const size_t init_capacity = 10;
	ava::Vector<int> vec(init_capacity);
	ASSERT_TRUE(vec_with_default_capacity.capacity() == init_capacity);
	ASSERT_TRUE(vec_with_default_capacity.size() == 0);
}

TEST(Vector, Constructor_with_size_and_value)
{
	const size_t init_size = 10;
	const int init_value = 5;
	ava::Vector<int> vec(init_size, init_value);
	ASSERT_TRUE(vec.size() == init_size);
	for (size_t i = 0; i < init_size; i++) {
		ASSERT_TRUE(vec[i] == init_value);
	}
}

TEST(Vector, Insert)
{
	ava::Vector<int> vec(20);
	for (size_t i = 0; i < 10; i++) {
		vec.push_back(i + 1);
	}
	vec.insert(6, 2, 0);
	int el_num5 = vec[4], el_num6 = vec[5], el_num7 = vec[6], el_num8 = vec[7], el_num9 = vec[8];
	bool is_ok = (el_num5 == 5) && (el_num6 == 6) && (el_num7 == 0) && (el_num8 == 0) && (el_num9 == 7);
	ASSERT_TRUE(is_ok);
}


TEST(Vector, Capacity)
{
	const size_t init_capacity = 15;
	ava::Vector<int> vec(init_capacity);
	const size_t capacity = vec.capacity();

	bool is_capacity_ok = (capacity == init_capacity);
	ASSERT_TRUE(is_capacity_ok);
}


TEST(Vector, Push_back)
{
	const size_t init_capacity = 5;
	ava::Vector<int> vec(init_capacity);
	for (size_t i = 0; i < init_capacity + 1; i++) {
		vec.push_back(i);
		ASSERT_TRUE(vec[i] == i);
	}
	ASSERT_TRUE(vec.capacity() > init_capacity);
}

class Vector_Object_For_Testing_Single_Vec : public testing::Test
{
public:
	Vector_Object_For_Testing_Single_Vec() :vec_(init_capacity_) {
		for (size_t i = 0; i < init_size_; i++) {
			vec_.push_back(i + 1);
		}
	}

protected:
	const size_t init_capacity_ = 15;
	const size_t init_size_ = 10;
	ava::Vector<double> vec_;
};

TEST_F(Vector_Object_For_Testing_Single_Vec, Copy_constructor)
{
	ava::Vector<double> copy_vec(vec_);
	ASSERT_TRUE(vec_.size() == copy_vec.size());
	ASSERT_TRUE(vec_.capacity() == copy_vec.capacity());
	for (size_t i = 0; i < init_size_; i++) {
		ASSERT_TRUE(vec_[i] == copy_vec[i]);
		ASSERT_TRUE(&vec_[i] != &copy_vec[i]);
	}
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Pop_back)
{
	for (size_t size = init_size_; size > 0; size--) {
		vec_.pop_back();
		ASSERT_TRUE(vec_.size() == size - 1);
	}
	ASSERT_THROW(vec_.pop_back(), std::length_error);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Resize_With_Reduction)
{
	vec_.resize(5, 0);

	size_t vec_new_size = vec_.size();

	bool is_new_size_ok = (vec_new_size == 5);

	ASSERT_TRUE(is_new_size_ok);

	double el_num1 = vec_[0], el_num2 = vec_[1], el_num3 = vec_[2], el_num4 = vec_[3], el_num5 = vec_[4];
	bool are_elements_ok = (el_num1 == 1) && (el_num2 == 2) && (el_num3 == 3) && (el_num4 == 4) && (el_num5 == 5);

	ASSERT_TRUE(are_elements_ok);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Resize_With_Bigger_Size)
{
	vec_.resize(12, 0);

	size_t vec_new_size = vec_.size();

	bool is_new_size_ok = (vec_new_size == 12);

	ASSERT_TRUE(is_new_size_ok);

	double el_num9 = vec_[8], el_num10 = vec_[9], el_num11 = vec_[10], el_num12 = vec_[11];
	bool are_elements_ok = (el_num9 == 9) && (el_num10 == 10) && (el_num11 == 0) && (el_num12 == 0);

	ASSERT_TRUE(are_elements_ok);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Resize_With_Bigger_Capacity)
{
	vec_.resize(17, 0);

	size_t vec_new_size = vec_.size(), vec_new_capacity = vec_.capacity();
	double el_num9 = vec_[8], el_num10 = vec_[9], el_num11 = vec_[10], el_num12 = vec_[11],
		el_num13 = vec_[12], el_num14 = vec_[13], el_num15 = vec_[14], el_num16 = vec_[15],
		el_num17 = vec_[16];

	bool is_new_size_ok = (vec_new_size == 17);

	ASSERT_TRUE(is_new_size_ok);

	bool is_new_cap_bigger = (vec_new_capacity > 15);

	ASSERT_TRUE(is_new_cap_bigger);

	bool are_elements_ok = (el_num9 == 9) && (el_num10 == 10) && (el_num11 == 0) && (el_num12 == 0) && (el_num13 == 0)
		&& (el_num14 == 0) && (el_num15 == 0) && (el_num16 == 0) && (el_num17 == 0);

	ASSERT_TRUE(are_elements_ok);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Assign_With_Count_Less_Than_Capacity_And_Less_Than_Size)
{
	vec_.assign(3, 0);

	size_t size = vec_.size(), capacity = vec_.capacity();
	bool is_size_ok = (size == 3);

	ASSERT_TRUE(is_size_ok);

	bool is_capacity_ok = (capacity == 15);

	ASSERT_TRUE(is_capacity_ok);

	double el_num1 = vec_[0], el_num2 = vec_[1], el_num3 = vec_[2];
	bool are_elements_ok = (el_num1 == 0) && (el_num2 == 0) && (el_num3 == 0);

	ASSERT_TRUE(are_elements_ok);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Assign_With_Count_Less_Than_Capacity_And_Bigger_Than_Size)
{
	vec_.assign(12, 0);

	size_t size = vec_.size(), capacity = vec_.capacity();
	bool is_size_ok = (size == 12);

	ASSERT_TRUE(is_size_ok);

	bool is_capacity_ok = (capacity == 15);

	ASSERT_TRUE(is_capacity_ok);

	double el_num10 = vec_[9], el_num11 = vec_[10], el_num12 = vec_[11];
	bool are_elements_ok = (el_num10 == 0) && (el_num11 == 0) && (el_num12 == 0);

	ASSERT_TRUE(are_elements_ok);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Assign_With_Count_Bigger_Than_Capacity_And_Bigger_Than_Size)
{
	vec_.assign(17, 0);

	size_t size = vec_.size(), capacity = vec_.capacity();
	bool is_size_ok = (size == 17);

	ASSERT_TRUE(is_size_ok);

	bool is_capacity_ok = (capacity > 15);

	ASSERT_TRUE(is_capacity_ok);

	double el_num15 = vec_[14], el_num16 = vec_[15], el_num17 = vec_[16];
	bool are_elements_ok = (el_num15 == 0) && (el_num16 == 0) && (el_num17 == 0);

	ASSERT_TRUE(are_elements_ok);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Reserve)
{
	const size_t new_less_capicity = 5;
	ASSERT_TRUE(new_less_capicity < init_capacity_);
	vec_.reserve(new_less_capicity);
	ASSERT_TRUE(vec_.capacity() == init_capacity_);

	const size_t new_bigger_capicity = 20;
	ASSERT_TRUE(new_bigger_capicity > init_capacity_);
	vec_.reserve(new_bigger_capicity);
	ASSERT_TRUE(vec_.capacity() == new_bigger_capicity);

	for (size_t i = 0; i < vec_.size(); i++) {
		ASSERT_TRUE(vec_[i] == i + 1);
	}
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Shrink_to_fit)
{
	vec_.shrink_to_fit();
	ASSERT_TRUE(init_size_ == vec_.size());
	ASSERT_TRUE(vec_.capacity() == init_size_);

	for (size_t i = 0; i < init_size_; i++) {
		ASSERT_TRUE(vec_[i] == i + 1);
	}
}

class Vector_Objects_For_Cheking_Equality : public testing::Test
{
public:
	Vector_Objects_For_Cheking_Equality() :
		init_vec(15), first_assigned_vec(17), secong_assigned_vec(19) {

		for (size_t i = 0; i < 3; i++) {
			init_vec.push_back(i + 1);
		}

		secong_assigned_vec = first_assigned_vec = init_vec;
	}
protected:
	ava::Vector<int> init_vec, first_assigned_vec, secong_assigned_vec;
};

TEST_F(Vector_Objects_For_Cheking_Equality, Check_Capacity_Equality)
{
	size_t init_cap = init_vec.capacity(),
		first_assigned_cap = first_assigned_vec.capacity(),
		second_assigned_cap = secong_assigned_vec.capacity();

	bool is_ok = (first_assigned_cap == init_cap) && (second_assigned_cap == init_cap);

	ASSERT_TRUE(is_ok);
}

TEST_F(Vector_Objects_For_Cheking_Equality, Check_Size_Equality)
{
	size_t init_size = init_vec.size(),
		first_assigned_size = first_assigned_vec.size(),
		second_assigned_size = secong_assigned_vec.size();

	bool is_ok = (first_assigned_size == init_size) && (second_assigned_size == init_size);

	ASSERT_TRUE(is_ok);
}

TEST_F(Vector_Objects_For_Cheking_Equality, Check_Elements_Equality)
{
	int init_el_num1 = init_vec[0], init_el_num2 = init_vec[1], init_el_num3 = init_vec[2],
		first_assigned_el_num1 = first_assigned_vec[0], first_assigned_el_num2 = first_assigned_vec[1], first_assigned_el_num3 = first_assigned_vec[2],
		second_assigned_el_num1 = secong_assigned_vec[0], second_assigned_el_num2 = secong_assigned_vec[1], second_assigned_el_num3 = secong_assigned_vec[2];


	bool is_ok = (first_assigned_el_num1 == init_el_num1) && (second_assigned_el_num1 == init_el_num1)
		&& (first_assigned_el_num2 == init_el_num2) && (second_assigned_el_num2 == init_el_num2)
		&& (first_assigned_el_num3 == init_el_num3) && (second_assigned_el_num3 == init_el_num3);

	ASSERT_TRUE(is_ok);
}

TEST_F(Vector_Objects_For_Cheking_Equality, Check_Elements_Addreses_Not_Equality)
{
	const int * init_p_num1 = &init_vec[0], * init_p_num2 = &init_vec[1], * init_p_num3 = &init_vec[2],
		* first_assigned_p_num1 = &first_assigned_vec[0], * first_assigned_p_num2 = &first_assigned_vec[1], * first_assigned_p_num3 = &first_assigned_vec[2],
		* second_assigned_p_num1 = &secong_assigned_vec[0], * second_assigned_p_num2 = &secong_assigned_vec[1], * second_assigned_p_num3 = &secong_assigned_vec[2];


	bool is_ok = (first_assigned_p_num1 != init_p_num1) && (second_assigned_p_num1 != init_p_num1)
		&& (first_assigned_p_num2 != init_p_num2) && (second_assigned_p_num2 != init_p_num2)
		&& (first_assigned_p_num3 != init_p_num3) && (second_assigned_p_num3 != init_p_num3);

	ASSERT_TRUE(is_ok);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
	return 0;
}