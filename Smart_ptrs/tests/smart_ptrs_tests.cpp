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
	// p1 - �������� ������ auto_ptr ������� ������������� ������� p2
	// default_ptr - ��������� ������� �������� � �������� �������
	auto_ptr<int> p1(new int(1)), p2;
	int * default_ptr = p1.get();
	// WHEN
	p2 = p1;
	// THEN
	// 
	// ���������, ��� �������� �������� ������� � ������� p2 � ��� ������ p1 ������ �� ������� ��������
	ASSERT_TRUE(p2.get() == default_ptr);
	ASSERT_TRUE(p1.get() == nullptr);
}

TEST(unique_ptr, Assign_ptrs)
{
	// GIVEN
	//
	// p1 - �������� ������ unique_ptr ������� ������������� ������� p2
	// default_ptr - ��������� ������� �������� � �������� �������
	unique_ptr<int> p1(new int(1)), p2;
	int * default_ptr = p1.get();
	// WHEN
	//p2 = p1;// ������ ����������!
	// THEN
	//
	// ���������, ��� �������� �������� ������� � ������� p2 � ��� ������ p1 ������ �� ������� ��������
	ASSERT_TRUE(p2.get() == default_ptr);
	ASSERT_TRUE(p1.get() == nullptr);
}

TEST(unique_ptr, Move_constructor)
{
	// GIVEN
	//
	// val - ���������� �� ��� ��������� ���������������� ��������� ������
	// p1 - ������ ����������� � ������� ������������ �����������
	const int val = 10;
	unique_ptr<int> p(unique_ptr<int>(new int(val)));

	// WHEN
	//
	// ������ �� ������

	// THEN
	//
	// ���������, ��� ������ � �������� ���������� �������
	ASSERT_TRUE(*p == val);
}

TEST(unique_ptr, Move_assignment)
{
	// GIVEN
	//
	// val_1, val_2 - ����������� �� ��� ��������� ���������������� ������� �1 � ��������� ������ ��������������
	// �1, �2 - ������� unique_ptr
	const int val_1 = 10, val_2 = 20;
	unique_ptr<int> p(new int(val_1));

	// WHEN
	//
	//����������� ��������� ������ ������� �
	p = unique_ptr<int>(new int(val_2));

	// THEN
	//
	// ���������, ��� ������ � ���� ���������� �������, ������� ����������� ��������� �������
	ASSERT_TRUE(*p == val_2);

}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("PAUSE");
	return 0;
}