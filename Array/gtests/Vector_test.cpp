#include <iostream>
#include"gtest\gtest.h"
#include "Array.h"

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

class Vector_Object_For_Resizing_And_Assigning : public testing::Test
{
public:
	Vector_Object_For_Resizing_And_Assigning() :vec_(15) {
		for (size_t i = 0; i < 10; i++) {
			vec_.push_back(i + 1);
		}
	}

protected:
	ava::Vector<double> vec_;
};

TEST_F(Vector_Object_For_Resizing_And_Assigning, Resize_With_Reduction)
{
	vec_.resize(5, 0);

	size_t vec_new_size = vec_.size();

	bool is_new_size_ok = (vec_new_size == 5);

	ASSERT_TRUE(is_new_size_ok);

	double el_num1 = vec_[0], el_num2 = vec_[1], el_num3 = vec_[2], el_num4 = vec_[3], el_num5 = vec_[4];
	bool are_elements_ok = (el_num1 == 1) && (el_num2 == 2) && (el_num3 == 3) && (el_num4 == 4) && (el_num5 == 5);

	ASSERT_TRUE(are_elements_ok);
}

TEST_F(Vector_Object_For_Resizing_And_Assigning, Resize_With_Bigger_Size)
{
	vec_.resize(12, 0);

	size_t vec_new_size = vec_.size();

	bool is_new_size_ok = (vec_new_size == 12);

	ASSERT_TRUE(is_new_size_ok);

	double el_num9 = vec_[8], el_num10 = vec_[9], el_num11 = vec_[10], el_num12 = vec_[11];
	bool are_elements_ok = (el_num9 == 9) && (el_num10 == 10) && (el_num11 == 0) && (el_num12 == 0);

	ASSERT_TRUE(are_elements_ok);
}

TEST_F(Vector_Object_For_Resizing_And_Assigning, Resize_With_Bigger_Capacity)
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

TEST_F(Vector_Object_For_Resizing_And_Assigning, Assign_With_Count_Less_Than_Capacity_And_Less_Than_Size)
{
	vec_.assign(3, 0);

	size_t size = vec_.size(), capacity = vec_.capacity();
	bool is_size_ok = (size == 10);

	ASSERT_TRUE(is_size_ok);

	bool is_capacity_ok = (capacity == 15);

	ASSERT_TRUE(is_capacity_ok);

	double el_num1 = vec_[0], el_num2 = vec_[1], el_num3 = vec_[2], el_num4 = vec_[3], el_num5 = vec_[4];
	bool are_elements_ok = (el_num1 == 0) && (el_num2 == 0) && (el_num3 == 0) && (el_num4 == 4) && (el_num5 == 5);

	ASSERT_TRUE(are_elements_ok);
}

TEST_F(Vector_Object_For_Resizing_And_Assigning, Assign_With_Count_Less_Than_Capacity_And_Bigger_Than_Size)
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

TEST_F(Vector_Object_For_Resizing_And_Assigning, Assign_With_Count_Bigger_Than_Capacity_And_Bigger_Than_Size)
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

int main(int argc, char** argv) {

	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
	return 0;
}