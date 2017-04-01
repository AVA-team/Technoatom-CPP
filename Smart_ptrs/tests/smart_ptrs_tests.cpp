#include <iostream>
#include"auto_ptr.h"
#include"unique_ptr.h"
#include"shared_ptr.h"
#include "gtest\gtest.h"

using ava::auto_ptr;
using ava::unique_ptr;
using ava::shared_ptr;

TEST(Auto_ptr, Assign_ptrs)
{
	// GIVEN
	//
	// p1 - исходный объект auto_ptr который присваивается объекту p2
	// default_ptr - указатель который хранится в исходном объекте
	auto_ptr<int> p1(new int(1)), p2;
	int * default_ptr = p1.get();
	// WHEN
	p2 = p1;
	// THEN
	// 
	// Проверяем, что владение ресурсом перешло к объекту p2 и что объект p1 больше не владеет ресурсом
	ASSERT_TRUE(p2.get() == default_ptr);
	ASSERT_TRUE(p1.get() == nullptr);
}

TEST(Auto_ptr, Reset)
{
	// GIVEN
	//
	// val - начальное значение, указатель на которое хранится в р1
	// new_val - значение, указатель на которое БУДЕТ хранится в р1 после вызова reset
	// p1 - исходный объект auto_ptr
	const int val = 10, new_val = 20;
	auto_ptr<int> p1(new int(val));

	// WHEN
	//
	// Устанавливаем новый ресурс, в котором хранится значчение new_val
	// В переменную curr_val записываем текущее значение, которое хранится в р1
	p1.reset(new int(new_val));
	int curr_val = *p1;

	// THEN
	// 
	// Проверяем, что умный указатель хранит новое значение
	ASSERT_TRUE(curr_val == new_val);
}

TEST(Auto_ptr, Release)
{
	// GIVEN
	//
	// val - начальное значение, указатель на которое хранится в р1
	// p1 - исходный объект auto_ptr
	const int val = 10;
	auto_ptr<int> p1(new int(val));

	// WHEN
	//
	// Освобождаем ресурси сохраняем указатель на него в переменную resource.
	// В переменную holding_resource сохраняем указатель на текущий ресурс объекта р1
	int* resource = p1.release(), *holding_resource = p1.get();

	// THEN
	// 
	// Проверяем, что умный указатель освободил ресурс и что ресурс не изменился
	ASSERT_TRUE(holding_resource == nullptr);
	ASSERT_TRUE(*resource == val);
}

TEST(Unique_ptr, Assign_ptrs)
{
	// GIVEN
	//
	// p1 - исходный объект unique_ptr который присваивается объекту p2
	// default_ptr - указатель который хранится в исходном объекте
	unique_ptr<int> p1(new int(1)), p2;
	int * default_ptr = p1.get();
	// WHEN
	//p2 = p1;// ОШИБКА КОМПИЛЯЦИИ!
	// THEN
	//
	// Проверяем, что владение ресурсом перешло к объекту p2 и что объект p1 больше не владеет ресурсом
	//ASSERT_TRUE(p2.get() == default_ptr);
	//ASSERT_TRUE(p1.get() == nullptr);
}

TEST(Unique_ptr, Move_constructor)
{
	// GIVEN
	//
	// val - указателем на эту константу инициализируется временный объект
	// p1 - объект построенный с помощью конструктора перемещения
	const int val = 10;
	unique_ptr<int> p(unique_ptr<int>(new int(val)));

	// WHEN
	//
	// Ничего не делаем

	// THEN
	//
	// Проверяем, что объект р является владельцем ресурса
	ASSERT_TRUE(*p == val);
}

TEST(Unique_ptr, Move_assignment)
{
	// GIVEN
	//
	// val_1, val_2 - указателями на эти константы инициализируются объекты р1 и временный объект соответственно
	// р1, р2 - объекты unique_ptr
	const int val_1 = 10, val_2 = 20;
	unique_ptr<int> p(new int(val_1));

	// WHEN
	//
	//Присваиваем временный объект объекту р
	p = unique_ptr<int>(new int(val_2));

	// THEN
	//
	// Проверяем, что объект р стал владельцем ресурса, который принадлежал врменному объекту
	ASSERT_TRUE(*p == val_2);

}

TEST(Unique_ptr, Reset)
{
	// GIVEN
	//
	// val - начальное значение, указатель на которое хранится в р1
	// new_val - значение, указатель на которое БУДЕТ хранится в р1 после вызова reset
	// p1 - исходный объект auto_ptr
	const int val = 10, new_val = 20;
	unique_ptr<int> p1(new int(val));

	// WHEN
	//
	// Устанавливаем новый ресурс, в котором хранится значчение new_val
	// В переменную curr_val записываем текущее значение, которое хранится в р1
	p1.reset(new int(new_val));
	int curr_val = *p1;

	// THEN
	// 
	// Проверяем, что умный указатель хранит новое значение
	ASSERT_TRUE(curr_val == new_val);
}

TEST(Unique_ptr, Release)
{
	// GIVEN
	//
	// val - начальное значение, указатель на которое хранится в р1
	// p1 - исходный объект auto_ptr
	const int val = 10;
	unique_ptr<int> p1(new int(val));

	// WHEN
	//
	// Освобождаем ресурси сохраняем указатель на него в переменную resource.
	// В переменную holding_resource сохраняем указатель на текущий ресурс объекта р1
	int* resource = p1.release(), *holding_resource = p1.get();

	// THEN
	// 
	// Проверяем, что умный указатель освободил ресурс и что ресурс не изменился
	ASSERT_TRUE(holding_resource == nullptr);
	ASSERT_TRUE(*resource == val);
}

TEST(Shared_Ptr, Constructor)
{
	// GIVEN
	//
	// val - значение, указатель на которое хранится в умном указателе
	const int val = 5;

	// WHEN
	//
	// Создаём умный указатель, который хранит значение val
	shared_ptr<int> ip(new int(val));

	// THEN
	//
	// Проверяем, что хранимое значение совпадает с val
	ASSERT_TRUE(*ip == val);
}

TEST(Shared_Ptr, Copy_Constructor)
{
	// GIVEN
	//
	// val - значение, указатель на которое хранится в умном указателе ip
	// iptr - исходный умный указатель
	const int val = 5;
	shared_ptr<int> iptr(new int(val));

	// WHEN
	//
	// Создаём указатель copy_iptr с помощью копи-конструктора
	// В переменную use_count записываем число владельцев ресурса
	shared_ptr<int> copy_iptr(iptr);
	long int use_count = copy_iptr.use_count();

	// THEN
	//
	// Проверяем, что ресурсом владеют два объекта
	ASSERT_TRUE(use_count == 2);

}

TEST(Shared_Ptr, Arrow_Operator)
{
	// GIVEN
	//
	// val - начальное значение, указатель на которое хранится в умном указателе ip
	// new_val - новое значение, указатель на которое будет храниться в iptr
	// iptr - исходный умный указатель
	const int val = 5, new_val = 10;
	shared_ptr<int> iptr(new int(val));

	// WHEN
	//
	// Получаем указатель на ресурс с попмощью оператора ->
	// Присваиваем ресурсу новое значение
	// Записываем текущее значение, которое хранится в умном указателе, в переменную curr_val
	int* temp_ptr = iptr->get_ptr();
	*temp_ptr = new_val;
	int curr_val = *iptr;

	// THEN
	//
	// Проверяем, что текущее значение равно значению которое мы установили в последний раз
	ASSERT_TRUE(curr_val == new_val);
}

TEST(Shared_Ptr, Star_Operator)
{
	// GIVEN
	//
	// val - начальное значение, указатель на которое хранится в умном указателе iptr
	// iptr - исходный умный указатель
	const int val = 5;
	shared_ptr<int> iptr(new int(val));

	// WHEN
	//
	// Записываем текущее значение, которое хранится в умном указателе, в переменную curr_val
	int curr_val = *iptr;

	// THEN
	//
	// Проверяем, что текущее значение равно значению которое мы установили в последний раз
	ASSERT_TRUE(curr_val == val);
}

TEST(Shared_Ptr, Bool_Operator)
{
	// GIVEN
	//
	// iptr - исходный умный указатель, хранящий nullptr
	shared_ptr<int> iptr;

	// WHEN
	//
	// Используя приведение к bool, записываем хранит ли указатель nullptr в переменную is_nullptr
	bool is_nullptr = (bool)iptr;

	// THEN
	//
	// Проверяем, что iptr хранит nullptr
	ASSERT_TRUE(is_nullptr);
}

TEST(Shared_Ptr, Equal_Operator)
{
	// GIVEN
	//
	// val - начальное значение, указатель на которое хранится в умном указателе iptr
	// iptr - исходный умный указатель, хранящий nullptr
	// assigned_iptr - умный указатель, хранящий nullptr, который будет использова в операции присваивания
	const int val = 10;
	shared_ptr<int> iptr(new int(val)), assigned_iptr;

	// WHEN
	//
	// Присваиваем iptr указателю assigned_iptr
	// В переменную use_count записываем число владельцев ресурса
	// В переменную curr_val записываем значение хранящеейся в указателе
	assigned_iptr = iptr;
	long int use_count = iptr.use_count();
	int curr_val = *assigned_iptr;

	// THEN
	//
	// Проверяем, что число владельцев равно 2 и текущее значение равно val
	ASSERT_TRUE(use_count == 2);
	ASSERT_TRUE(curr_val == val);
}

TEST(Shared_Ptr, Swap)
{
	// GIVEN
	//
	// val_1 - значение, указатель на которое хранится в iptr_1
	// val_2 - значение, указатель на которое хранится в iptr_2
	const int val_1 = 10, val_2 = 20;
	shared_ptr<int> iptr_1(new int(val_1)), iptr_2(new int(val_2));

	// WHEN
	//
	// Меняем местами iptr_1 и iptr_2
	// Новые хранимые значения записываем в new_val_1 и new_val_2
	iptr_1.swap(iptr_2);
	int new_val_1 = *iptr_1, new_val_2 = *iptr_2;

	// THEN
	//
	// Проверяем, что хранимые значения поменялись местами
	ASSERT_TRUE(new_val_1 == val_2);
	ASSERT_TRUE(new_val_2 == val_1);
}

TEST(Shared_Ptr, Reset)
{
	// GIVEN
	//
	// val - значение, указатель на которое хранится в iptr
	// new_val - новое значение, указатель на которе будет храниться в iptr
	const int val = 10, new_val = 20;
	shared_ptr<int> iptr(new int(val));

	// WHEN
	//
	// Присваиваем iptr новый ресурс со значением new_val
	// Новое хранимое значение записываем в curr_val
	iptr.reset(new int(new_val));
	int curr_val = *iptr;

	// THEN
	//
	// Проверяем, что хранимые значения поменялись местами
	ASSERT_TRUE(curr_val == new_val);
}

TEST(Shared_Ptr, Unique)
{
	// GIVEN
	//
	// val - значение, указатель на которое хранится в iptr
	const int val = 10;
	shared_ptr<int> iptr(new int(val));

	// WHEN
	//
	// Создаём другого владельца another_owner
	// В переменную is_unique записываем является ли объект another_owner единственным (уникальным) владельцем
	shared_ptr<int> iptr_another_owner(iptr);
	bool is_unique = iptr_another_owner.unique();

	// THEN
	//
	// Проверяем, что another_owner не является единственным владельцем
	ASSERT_TRUE(is_unique == false);
}

TEST(Shared_Ptr, Use_count)
{
	// GIVEN
	//
	// val - значение, указатель на которое хранится в iptr
	const int val = 10;
	shared_ptr<int> iptr(new int(val));

	// WHEN
	//
	// Создаём два других объекта shared_ptr, которые владеют тем же ресурсом
	// В переменную use_count записываем число владельцев ресурса
	shared_ptr<int> iptr_owner_2(iptr), iptr_owner_3(iptr);
	auto use_count = iptr.use_count();

	// THEN
	//
	// Проверяем, что у ресурса три владельца
	ASSERT_TRUE(use_count == 3);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("PAUSE");
	return 0;
}