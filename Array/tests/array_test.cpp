#include <iostream>
#include "gtest\gtest.h"
#include "../implementation/array.hpp"

using ava::Array;

TEST(Array, Bracket_Operator)
{
	// GIVEN
	//
	// val - �������� ������� ����������� ������ arr ��������� �� ���� ���������
	const int val = 10;
	Array<int, 2> arr;
	arr.fill(val);

	// WHEN
	//
	// C�������� ������ � ������ �������� ������� � ���������� el_1 � el_2
	int el_1 = arr[0], el_2 = arr[1];

	// THEN
	//
	// ���������, ��� ������ � ������ �������� ������� ����� val
	ASSERT_TRUE(el_1 == val);
	ASSERT_TRUE(el_2 == val);
}

TEST(Array, At)
{
	// GIVEN
	//
	// val - �������� ������� ����������� ������ arr ��������� �� ���� ���������
	const int val = 10;
	Array<int, 2> arr;
	arr.fill(val);

	// WHEN
	//
	// C�������� ������ � ������ �������� ������� � ���������� el_1 � el_2
	int el_2 = arr.at(1);

	// THEN
	//
	// ���������, ��� ������ ������� ������� ����� val
	ASSERT_TRUE(el_2 == val);
}

TEST(Array, Front)
{
	// GIVEN
	//
	// val_1 - �������� ������� �������� ������� arr
	// val_2 - �������� ������� �������� ������� arr
	const int val_1 = 10, val_2 = 20;
	Array<int, 2> arr;
	arr[0] = val_1;
	arr[1] = val_2;

	// WHEN
	//
	// C�������� ������ ������� ������� � ���������� front_el
	int front_el = arr.front();

	// THEN
	//
	// ���������, ��� ������ ������� ������� ����� val_1
	ASSERT_TRUE(front_el == val_1);
}

TEST(Array, Back)
{
	// GIVEN
	//
	// val_1 - �������� ������� �������� ������� arr
	// val_2 - �������� ������� �������� ������� arr
	const int val_1 = 10, val_2 = 20;
	Array<int, 2> arr;
	arr[0] = val_1;
	arr[1] = val_2;

	// WHEN
	//
	// C�������� ��������� ������� ������� � ���������� back_el
	int back_el = arr.back();

	// THEN
	//
	// ���������, ��� ��������� ������� ������� ����� val_2
	ASSERT_TRUE(back_el == val_2);
}

TEST(Array, Empty)
{
	// GIVEN
	//
	// val - �������� ������� �������� ������� arr
	const int val = 10;
	Array<int, 1> arr;
	arr[0] = val;

	// WHEN
	//
	// C�������� � ���������� is_empty ���� �������� �� ������ ������
	bool is_empty = arr.empty();

	// THEN
	//
	// ���������, ��� ������ �� ����
	ASSERT_TRUE(!is_empty);
}

TEST(Array, Size)
{
	// GIVEN
	//
	// val - �������� ������� � ������� �������� ������� arr
	const int val = 10;
	Array<int, 3> arr;
	arr[0] = val;
	arr[1] = val;

	// WHEN
	//
	// C�������� ������ ������� � ���������� size
	auto size = arr.size();

	// THEN
	//
	// ���������, ��� ������ ������ 2 ��������
	ASSERT_TRUE(size == 2);
}

TEST(Array, Iterators)
{
	// GIVEN
	//
	// val - �������� ������� ������������� ���� ��������� ������� arr ����������
	// new_val - ����� �������� ��������� �������, ������� ������������� � ������� ��������� ����������
	const int val = 10, new_val = 20;
	Array<int, 3> arr;
	arr.fill(val);

	// WHEN
	//
	// � ������� ��������� ������������� ��� �������� ������� val
	// ������ ������� ������� ��������� � el_1, ������ � el_2, ������ � el_3
	for (ava::ContainerInterface<int>::ArrayIterator it = arr.begin(); it != arr.end(); ++it) {
		*it = new_val;
	}
	int el_1 = arr[0], el_2 = arr[1], el_3 = arr[2];

	// THEN
	//
	// ���������, ��� ��� �������� ������� ����� val
	ASSERT_TRUE(el_1 == new_val);
	ASSERT_TRUE(el_2 == new_val);
	ASSERT_TRUE(el_3 == new_val);
}

TEST(Array, Assigned_operator)
{
	// GIVEN
	//
	// val - �������� ������� ������������� ���� ��������� ������� init_arr
	// assigned_arr - ������ ������� �������� ������������� ������� init_arr
	const int val = 10;
	Array<int, 3> init_arr, assigned_arr;
	init_arr.fill(val);

	// WHEN
	//
	// � ������� ��������� ������������� ��� �������� ������� val
	// ������ ������� ������� ��������� � el_1, ������ � el_2, ������ � el_3
	assigned_arr = init_arr;
	int el_1 = assigned_arr[0], el_2 = assigned_arr[1], el_3 = assigned_arr[2];

	// THEN
	//
	// ���������, ��� ��� �������� ������� assigned_arr ����� val
	ASSERT_TRUE(el_1 == val);
	ASSERT_TRUE(el_2 == val);
	ASSERT_TRUE(el_3 == val);
}

TEST(Array, Swap)
{
	// GIVEN
	//
	// val_1 - �������� ������� ������������� ���� ��������� ������� arr
	// val_2 - �������� ������� ������������� ���� ��������� ������� another_arr
	// arr, another_arr - ������� ������� �������� �������
	const int val_1 = 10, val_2 = 20;
	Array<int, 1> arr, another_arr;
	arr.fill(val_1);
	another_arr.fill(val_2);

	// WHEN
	//
	// ������ ������� ������� � ��������� ����� �������� ��������� ������� � ���������� new_arr_el, new_another_arr_el
	arr.swap(another_arr);
	int new_arr_el = arr[0], new_another_arr_el = another_arr[0];

	// THEN
	//
	// ���������, ��� ������ ���������� �������
	ASSERT_TRUE(new_arr_el == val_2);
	ASSERT_TRUE(new_another_arr_el == val_1);
}