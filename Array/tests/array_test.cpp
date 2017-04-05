#include <iostream>
#include "gtest\gtest.h"
#include "../implementation/array.hpp"

using ava::Array;

TEST(Array, Bracket_Operator)
{
	// GIVEN
	//
	// val - значение которым заоплняется массив arr состоящий из двух элементов
	const int val = 10;
	Array<int, 2> arr;
	arr.fill(val);

	// WHEN
	//
	// Cохраняем первый и второй элементы массива в переменные el_1 и el_2
	int el_1 = arr[0], el_2 = arr[1];

	// THEN
	//
	// Проверяем, что первый и второй элементы массива равны val
	ASSERT_TRUE(el_1 == val);
	ASSERT_TRUE(el_2 == val);
}

TEST(Array, At)
{
	// GIVEN
	//
	// val - значение которым заоплняется массив arr состоящий из двух элементов
	const int val = 10;
	Array<int, 2> arr;
	arr.fill(val);

	// WHEN
	//
	// Cохраняем первый и второй элементы массива в переменные el_1 и el_2
	int el_2 = arr.at(1);

	// THEN
	//
	// Проверяем, что второй элемент массива равен val
	ASSERT_TRUE(el_2 == val);
}

TEST(Array, Front)
{
	// GIVEN
	//
	// val_1 - значение первого элемента массива arr
	// val_2 - значение второго элемента массива arr
	const int val_1 = 10, val_2 = 20;
	Array<int, 2> arr;
	arr[0] = val_1;
	arr[1] = val_2;

	// WHEN
	//
	// Cохраняем первый элемент массива в переменную front_el
	int front_el = arr.front();

	// THEN
	//
	// Проверяем, что первый элемент массива равен val_1
	ASSERT_TRUE(front_el == val_1);
}

TEST(Array, Back)
{
	// GIVEN
	//
	// val_1 - значение первого элемента массива arr
	// val_2 - значение второго элемента массива arr
	const int val_1 = 10, val_2 = 20;
	Array<int, 2> arr;
	arr[0] = val_1;
	arr[1] = val_2;

	// WHEN
	//
	// Cохраняем последний элемент массива в переменную back_el
	int back_el = arr.back();

	// THEN
	//
	// Проверяем, что последний элемент массива равен val_2
	ASSERT_TRUE(back_el == val_2);
}

TEST(Array, Empty)
{
	// GIVEN
	//
	// val - значение первого элемента массива arr
	const int val = 10;
	Array<int, 1> arr;
	arr[0] = val;

	// WHEN
	//
	// Cохраняем в переменную is_empty флаг является ли массив пустым
	bool is_empty = arr.empty();

	// THEN
	//
	// Проверяем, что массив не пуст
	ASSERT_TRUE(!is_empty);
}

TEST(Array, Size)
{
	// GIVEN
	//
	// val - значение первого и второго элемента массива arr
	const int val = 10;
	Array<int, 3> arr;
	arr[0] = val;
	arr[1] = val;

	// WHEN
	//
	// Cохраняем размер массива в переменную size
	auto size = arr.size();

	// THEN
	//
	// Проверяем, что массив хранит 2 элемента
	ASSERT_TRUE(size == 2);
}

TEST(Array, Iterators)
{
	// GIVEN
	//
	// val - значение которое присваивается всем элементам массива arr изначально
	// new_val - новое значение элементов массива, которое присваивается с помощью механизма итераторов
	const int val = 10, new_val = 20;
	Array<int, 3> arr;
	arr.fill(val);

	// WHEN
	//
	// С попощью итератора устанавливаем все элементы равными val
	// Первый элемент массива сохраняем в el_1, второй в el_2, третий в el_3
	for (ava::ContainerInterface<int>::ArrayIterator it = arr.begin(); it != arr.end(); ++it) {
		*it = new_val;
	}
	int el_1 = arr[0], el_2 = arr[1], el_3 = arr[2];

	// THEN
	//
	// Проверяем, что все элементы массива равны val
	ASSERT_TRUE(el_1 == new_val);
	ASSERT_TRUE(el_2 == new_val);
	ASSERT_TRUE(el_3 == new_val);
}

TEST(Array, Assigned_operator)
{
	// GIVEN
	//
	// val - значение которое присваивается всем элементам массива init_arr
	// assigned_arr - массив который создаётся присваиванием массива init_arr
	const int val = 10;
	Array<int, 3> init_arr, assigned_arr;
	init_arr.fill(val);

	// WHEN
	//
	// С попощью итератора устанавливаем все элементы равными val
	// Первый элемент массива сохраняем в el_1, второй в el_2, третий в el_3
	assigned_arr = init_arr;
	int el_1 = assigned_arr[0], el_2 = assigned_arr[1], el_3 = assigned_arr[2];

	// THEN
	//
	// Проверяем, что все элементы массива assigned_arr равны val
	ASSERT_TRUE(el_1 == val);
	ASSERT_TRUE(el_2 == val);
	ASSERT_TRUE(el_3 == val);
}

TEST(Array, Swap)
{
	// GIVEN
	//
	// val_1 - значение которое присваивается всем элементам массива arr
	// val_2 - значение которое присваивается всем элементам массива another_arr
	// arr, another_arr - массивы которые меняются данными
	const int val_1 = 10, val_2 = 20;
	Array<int, 1> arr, another_arr;
	arr.fill(val_1);
	another_arr.fill(val_2);

	// WHEN
	//
	// Меняем объекты местами и сохраняем новые значения элементов массива в переменные new_arr_el, new_another_arr_el
	arr.swap(another_arr);
	int new_arr_el = arr[0], new_another_arr_el = another_arr[0];

	// THEN
	//
	// Проверяем, что данные поменялись местами
	ASSERT_TRUE(new_arr_el == val_2);
	ASSERT_TRUE(new_another_arr_el == val_1);
}