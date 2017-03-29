#include <iostream>
#include"auto_ptr.h"
#include"unique_ptr.h"
#include"shared_ptr.h"
#include "gtest\gtest.h"

using ava::auto_ptr;
using ava::unique_ptr;
using ava::shared_ptr;

TEST(auto_ptr, Assign_ptrs)
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

TEST(unique_ptr, Assign_ptrs)
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
	ASSERT_TRUE(p2.get() == default_ptr);
	ASSERT_TRUE(p1.get() == nullptr);
}

TEST(unique_ptr, Move_constructor)
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

TEST(unique_ptr, Move_assignment)
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

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("PAUSE");
	return 0;
}