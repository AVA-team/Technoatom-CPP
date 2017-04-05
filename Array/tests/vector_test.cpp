#include <iostream>
#include "gtest\gtest.h"
#include "../implementation/vector.hpp"

TEST(Vector, Constructor_with_capacity)
{
	// GIVEN:
	//
	ava::Vector<int> vec_default;
	const size_t init_capacity = 15;
	// WHEN:
	//
	ava::Vector<int> vec(init_capacity);
	// THEN:
	//
	std::size_t vec_default_capacity = vec_default.capacity();
	std::size_t vec_default_size = vec_default.size();
	ASSERT_TRUE(vec_default_capacity == ava::default_capacity);
	ASSERT_TRUE(vec_default_size == 0);
	ASSERT_TRUE(vec.capacity() == init_capacity);
	ASSERT_TRUE(vec.size() == 0);
}

TEST(Vector, Constructor_with_size_and_value)
{
	// GIVEN:
	//
	const size_t init_size = 2;
	const int init_value = 5;
	// WHEN:
	//
	ava::Vector<int> vec(init_size, init_value);
	// THEN:
	//
	ASSERT_TRUE(vec.size() == init_size);
	ASSERT_TRUE(vec[0] == init_value);
	ASSERT_TRUE(vec[1] == init_value);
}

TEST(Vector, Insert)
{
	// GIVEN:
	//
	int first_el = 1, second_el = 2, val_to_insert = 0;
	std::size_t insert_pos = 1, insert_count = 2;
	ava::Vector<int> vec;
	vec.push_back(first_el);
	vec.push_back(second_el);
	// WHEN:
	//
	vec.insert(insert_pos, insert_count, val_to_insert);
	// THEN:
	//
	int first_inserted_el = vec[insert_pos],
		second_inserted_el = vec[insert_pos + 1];
	ASSERT_TRUE( first_inserted_el == val_to_insert && second_inserted_el == val_to_insert);
}


TEST(Vector, Push_back)
{
	// GIVEN:
	//
	ava::Vector<int> vec;
	int value_to_push = 15;
	// WHEN:
	//
	vec.push_back(value_to_push);
	// THEN:
	//
	ASSERT_TRUE(vec.back() == value_to_push);
}

TEST(Vector, Push_back_with_auto_incrementing_capacity)
{
	// GIVEN:
	//
	std::size_t init_capacity = 2;
	ava::Vector<int> vec(init_capacity);
	vec.push_back(10);
	vec.push_back(20);
	// WHEN:
	//
	vec.push_back(30);
	// THEN:
	//
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

	// WHEN:
	// 
	ava::Vector<int> copy_vec(vec_);
	// THEN:
	//
	ASSERT_TRUE(vec_.size() == copy_vec.size());
	ASSERT_TRUE(vec_.capacity() == copy_vec.capacity());
	ASSERT_TRUE(copy_vec[0] == vec_[0]);
	ASSERT_TRUE(copy_vec[1] == vec_[1]);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Pop_back)
{
	// GIVEN:
	//

	// WHEN:
	// 
	vec_.pop_back();
	// THEN:
	//
	ASSERT_TRUE(vec_.size() == (init_size_ - 1));
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Resize_With_Reduction)
{
	// GIVEN:
	//

	// WHEN:
	//
	vec_.resize(1);
	// THEN:
	//
	std::size_t vec_new_size = vec_.size();
	ASSERT_TRUE(vec_new_size == 1);
	ASSERT_TRUE(vec_[0] == 10);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Resize_With_Bigger_Size)
{
	// GIVEN:
	//
	const int value_for_new_elements = 777;
	// WHEN:
	//
	vec_.resize(3, value_for_new_elements);
	// THEN:
	//
	std::size_t vec_new_size = vec_.size();
	ASSERT_TRUE(vec_new_size == 3);
	ASSERT_TRUE(vec_[0] == 10);
	ASSERT_TRUE(vec_[1] == 20);
	ASSERT_TRUE(vec_[2] == value_for_new_elements);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Resize_With_Bigger_Capacity)
{
	// GIVEN:
	//
	const int value_for_new_elements = 777;
	// WHEN:
	//
	vec_.resize(4, value_for_new_elements);
	// THEN:
	//
	std::size_t vec_new_size = vec_.size(), vec_new_capacity = vec_.capacity();
	ASSERT_TRUE(vec_new_size == 4);
	ASSERT_TRUE(vec_new_capacity > init_capacity_);
	ASSERT_TRUE(vec_[2] == value_for_new_elements);
	ASSERT_TRUE(vec_[3] == value_for_new_elements);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Assign_With_Count_Less_Than_Capacity_And_Less_Than_Size)
{
	// GIVEN:
	//
	const int value_for_new_elements = 777;
	// WHEN:
	//
	vec_.assign(1, value_for_new_elements);
	// THEN:
	//
	size_t vec_size = vec_.size(), vec_capacity = vec_.capacity();
	ASSERT_TRUE(vec_size == 1);
	ASSERT_TRUE(vec_capacity == init_capacity_);
	ASSERT_TRUE(vec_[0] == value_for_new_elements);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Assign_With_Count_Less_Than_Capacity_And_Bigger_Than_Size)
{
	// GIVEN:
	//
	const int value_for_new_elements = 777;
	// WHEN:
	//
	vec_.assign(3, value_for_new_elements);
	// THEN:
	//
	std::size_t vec_size = vec_.size(), vec_capacity = vec_.capacity();
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
	const int value_for_new_elements = 777;
	// WHEN:
	//
	vec_.assign(4, value_for_new_elements);
	// THEN:
	//
	size_t vec_size = vec_.size(), vec_capacity = vec_.capacity();
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
	const size_t new_less_capicity = 2;
	// WHEN:
	//
	vec_.reserve(new_less_capicity);
	// THEN:
	//
	ASSERT_TRUE(vec_.size() == init_size_);
	ASSERT_TRUE(vec_.capacity() == init_capacity_);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Reserve_with_bigger_capacity)
{
	// GIVEN:
	//
	const size_t new_bigger_capicity = 4;
	// WHEN:
	//
	vec_.reserve(new_bigger_capicity);
	// THEN:
	//
	ASSERT_TRUE(vec_.size() == init_size_);
	ASSERT_TRUE(vec_.capacity() > init_capacity_);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Shrink_to_fit)
{
	// GIVEN:
	//

	// WHEN:
	//
	// —окращаем вместимость вектора до текущего размера
	vec_.shrink_to_fit();
	// THEN:
	//
	ASSERT_TRUE(vec_.size() == init_size_);
	ASSERT_TRUE(vec_.capacity() == init_size_);
}

//!  ласс, который настраивает объект вектора, который используетс€ в тестах оператора присваивани€
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

	// WHEN
	// 

	// THEN
	//
	// ѕровер€ем, что вместимости двух присвоинных векторов равны вместимости исходного вектора
	size_t init_cap = init_vec_.capacity(),
		first_assigned_cap = first_assigned_vec_.capacity(),
		second_assigned_cap = second_assigned_vec_.capacity();
	ASSERT_TRUE(first_assigned_cap == init_cap);
	ASSERT_TRUE(second_assigned_cap == init_cap);
}

TEST_F(Vector_Objects_For_Cheking_Equality, Check_Size_Equality)
{
	// GIVEN:
	// 

	// WHEN
	// 

	// THEN
	//
	size_t init_size = init_vec_.size(),
		first_assigned_size = first_assigned_vec_.size(),
		second_assigned_size = second_assigned_vec_.size();
	ASSERT_TRUE(first_assigned_size == init_size);
	ASSERT_TRUE(second_assigned_size == init_size);
}

TEST_F(Vector_Objects_For_Cheking_Equality, Check_Elements_Equality)
{
	// GIVEN:
	// 

	// WHEN
	// 

	// THEN
	//
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
	std::size_t vec_size = 2;
	const int value = 777;
	// WHEN
	//
	ava::Vector<int> vec(ava::Vector<int>(vec_size, value));
	// THEN
	//
	ASSERT_TRUE(vec.size() == vec_size);
	ASSERT_TRUE(vec.capacity() == vec_size);
	ASSERT_TRUE(vec[0] == value);
	ASSERT_TRUE(vec[1] == value);
}

TEST(Vector, Move_assignment)
{
	// GIVEN:
	// 
	std::size_t vec_size = 2;
	const int value = 777;
	ava::Vector<int> vec;
	// WHEN:
	// 
	vec = ava::Vector<int>(vec_size, value);
	// THEN
	//
	ASSERT_TRUE(vec.size() == vec_size);
	ASSERT_TRUE(vec.capacity() == vec_size);
	ASSERT_TRUE(vec[0] == value);
	ASSERT_TRUE(vec[1] == value);
}

TEST(Vector, Initializer_list)
{
	// GIVEN
	//
	const int val_1 = 1, val_2 = 3;
	// WHEN
	//
	ava::Vector<int> vi = { val_1, val_2 };
	// THEN
	//
	int el_1 = vi[0], el_2 = vi[1];
	ASSERT_TRUE(el_1 == val_1);
	ASSERT_TRUE(el_2 == val_2);
}


///////////////////////////////////////////////////////////////////////////////
// VECTOR<BOOL> TESTS
///////////////////////////////////////////////////////////////////////////////

TEST(Vector_bool, Copy_constructor)
{
	// GIVEN
	//
	ava::Vector<bool> vb;
	bool first_bit_val = true, second_bit_val = false;
	vb[0] = first_bit_val;
	vb[1] = second_bit_val;
	// WHEN
	//
	ava::Vector<bool> copy_vb(vb);
	// THEN
	//
	bool first_bit_copy = copy_vb[0], second_bit_copy = copy_vb[1];
	ASSERT_TRUE(vb.size() == copy_vb.size());
	ASSERT_TRUE(first_bit_copy == first_bit_val);
	ASSERT_TRUE(second_bit_copy == second_bit_val);
}

TEST(Vector_bool, Initializer_list)
{
	// GIVEN
	//
	bool first_bit_val = true, second_bit_val = false;
	// WHEN
	//
	ava::Vector<bool> vb = { first_bit_val, second_bit_val };
	// THEN
	//
	bool first_bit = vb[0], second_bit = vb[1];
	ASSERT_TRUE(vb.size() == 2);
	ASSERT_TRUE(first_bit == first_bit_val);
	ASSERT_TRUE(second_bit == second_bit_val);
}

TEST(Vector_bool, Move_constructor)
{
	// GIVEN
	//
	// size - размер вектора
	// bits_val - значение всех битов вектора
	std::size_t size = 2;
	bool bits_val = true;
	// WHEN
	//
	ava::Vector<bool> vb(ava::Vector<bool>(2, bits_val));
	// THEN
	//
	bool first_bit = vb[0], second_bit = vb[1];
	ASSERT_TRUE(vb.size() == size);
	ASSERT_TRUE(first_bit == bits_val);
	ASSERT_TRUE(second_bit == bits_val);
}

TEST(Vector_bool, Assignment_operator)
{
	// GIVEN
	//
	// initial_size - размер исходного вектора
	// first_bit_val, second_bit_val - значение первых двух битов исходного вектора
	// vb - исходный вектор
	// vb_assigned - вектор которому будут присвоен вектор vb
	std::size_t initial_size = 2;
	bool first_bit_val = true, second_bit_val = false;
	ava::Vector<bool> vb = { first_bit_val, second_bit_val }, vb_assigned;
	// WHEN
	//
	// ѕрисвоение
	vb_assigned = vb;
	// THEN
	//
	// ѕровер€ем что исходный и присвоенные векторы равны
	auto size = vb_assigned.size();
	bool first_bit = vb_assigned[0], second_bit = vb[1];
	ASSERT_TRUE(size == initial_size);
	ASSERT_TRUE(first_bit == first_bit_val);
	ASSERT_TRUE(second_bit == second_bit_val);
}

TEST(Vector_bool, Move_assignment_operator)
{
	// GIVEN
	//
	std::size_t initial_size = 2;
	bool first_bit_val = true, second_bit_val = false;
	ava::Vector<bool> vb;
	// WHEN
	//
	vb = ava::Vector<bool>{ first_bit_val, second_bit_val };
	// THEN
	//
	auto size = vb.size();
	bool first_bit = vb[0], second_bit = vb[1];
	ASSERT_TRUE(size == initial_size);
	ASSERT_TRUE(first_bit == first_bit_val);
	ASSERT_TRUE(second_bit == second_bit_val);
}

TEST(Vector_bool, Bracket_operator)
{
	// GIVEN
	//
	bool first_bit_val = true, second_bit_val = false, new_first_bit_val = false;
	ava::Vector<bool> vb{ first_bit_val, second_bit_val };
	// WHEN
	//
	vb[0] = new_first_bit_val;
	auto first_bit = vb.front();
	// THEN
	//
	ASSERT_TRUE(first_bit == new_first_bit_val);
}

TEST(Vector_bool, Swap)
{
	// GIVEN
	//
	bool initial_first_bit_vb1 = true, initial_second_bit_vb1 = false,
		initial_first_bit_vb2 = initial_second_bit_vb1, initial_second_bit_vb2 = initial_first_bit_vb1;
	ava::Vector<bool> vb1{ true, false }, vb2{ false, true };
	// WHEN
	//
	vb1.swap(vb2);
	// THEN
	//
	bool first_bit_vb1 = vb1[0], second_bit_vb1 = vb1[1];
	ASSERT_TRUE(vb1.size() == vb2.size());
	ASSERT_TRUE(first_bit_vb1 == initial_first_bit_vb2);
	ASSERT_TRUE(second_bit_vb1 == initial_second_bit_vb2);
}

TEST(Vector_bool, Push_back)
{
	// GIVEN
	//
	bool first_bit_val = false, val_to_push = true;
	ava::Vector<bool> vb(2, first_bit_val);
	// WHEN
	//
	vb.push_back(val_to_push);
	// THEN
	//
	bool last_bit = vb[2];
	ASSERT_TRUE(last_bit == val_to_push);
}

TEST(Vector_bool, Push_back_with_full_vector)
{
	// GIVEN
	//
	bool bits_val = false, val_to_push = true;
	ava::Vector<bool> vb(32, bits_val);
	vb.shrink_to_fit();
	// WHEN
	//
	vb.push_back(val_to_push);
	// THEN
	//
	auto last_bit = vb[32];
	ASSERT_TRUE(last_bit == val_to_push);
}

TEST(Vector_bool, Insert)
{
	// GIVEN
	//
	bool bits_val = false, val_to_insert = true;
	std::size_t initial_size = 32;
	ava::Vector<bool> vb(initial_size, bits_val);
	vb.shrink_to_fit();
	std::size_t insert_pos = 20, insert_count = 2;
	// WHEN
	//
	vb.insert(insert_pos, insert_count, val_to_insert);
	// THEN
	//
	bool first_inserted_bit = vb[insert_pos],
		second_inserted_bit = vb[insert_pos + 1];
	ASSERT_TRUE(vb.size() == (initial_size + insert_count));
	ASSERT_TRUE(first_inserted_bit == val_to_insert);
	ASSERT_TRUE(second_inserted_bit == val_to_insert);
}

TEST(Vector_bool, Resize)
{
	// GIVEN
	//
	std::size_t new_size = 3;
	bool val_for_new_bits = true;
	ava::Vector<bool> vb{ false, false };
	// WHEN
	//
	vb.resize(3, val_for_new_bits);
	// THEN
	//
	auto new_actual_size = vb.size();
	bool new_bit = vb.back();
	ASSERT_TRUE(new_actual_size == new_size);
	ASSERT_TRUE(new_bit == val_for_new_bits);
}

TEST(Vector_bool, Assign)
{
	// GIVEN
	//
	bool initial_bits_val = false, new_bits_val = true;
	std::size_t new_size = 2;
	ava::Vector<bool> vb(1, initial_bits_val);
	// WHEN
	//
	vb.assign(new_size, new_bits_val);
	// THEN
	//
	std::size_t new_actual_size = vb.size();
	bool new_first_bit_val = vb[0], new_second_bit_val = vb[1];
	ASSERT_TRUE(new_actual_size == new_size);
	ASSERT_TRUE(new_first_bit_val == new_bits_val);
	ASSERT_TRUE(new_second_bit_val == new_bits_val);
}

TEST(Vector_bool, At)
{
	// GIVEN
	//
	bool initial_first_bit = true;
	ava::Vector<bool> vb(1, initial_first_bit);
	// WHEN
	//
	bool first_bit = vb.at(0);
	// THEN
	//
	ASSERT_TRUE(first_bit == initial_first_bit);
}

TEST(Vector_bool, Front)
{
	// GIVEN
	//
	bool first_bit_val = true,
		second_bit_val = false;
	ava::Vector<bool> vb{ first_bit_val, second_bit_val };
	// WHEN
	//
	bool front_bit = vb.front();
	// THEN
	//
	ASSERT_TRUE(front_bit == first_bit_val);
}

TEST(Vector_bool, Back)
{
	// GIVEN
	//
	bool first_bit_val = true,
		second_bit_val = false;
	ava::Vector<bool> vb{ first_bit_val, second_bit_val };
	// WHEN
	//
	bool back_bit = vb.back();
	// THEN
	//
	ASSERT_TRUE(back_bit == second_bit_val);
}

TEST(Vector_bool, Iterators)
{
	// GIVEN
	//
	bool initial_bits_val = false,
		new_bits_val = true;
	ava::Vector<bool> vb(2, initial_bits_val);
	// WHEN
	//
	for (auto it = vb.begin(); it != vb.end(); ++it) {
		*it = new_bits_val;
	}
	// THEN
	bool first_bit = vb[0], second_bit = vb[1];
	ASSERT_TRUE(first_bit == new_bits_val);
	ASSERT_TRUE(second_bit == new_bits_val);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
	return 0;
}
