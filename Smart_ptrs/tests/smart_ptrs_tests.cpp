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

TEST(Auto_ptr, Reset)
{
	// GIVEN
	//
	// val - ��������� ��������, ��������� �� ������� �������� � �1
	// new_val - ��������, ��������� �� ������� ����� �������� � �1 ����� ������ reset
	// p1 - �������� ������ auto_ptr
	const int val = 10, new_val = 20;
	auto_ptr<int> p1(new int(val));

	// WHEN
	//
	// ������������� ����� ������, � ������� �������� ��������� new_val
	// � ���������� curr_val ���������� ������� ��������, ������� �������� � �1
	p1.reset(new int(new_val));
	int curr_val = *p1;

	// THEN
	// 
	// ���������, ��� ����� ��������� ������ ����� ��������
	ASSERT_TRUE(curr_val == new_val);
}

TEST(Auto_ptr, Release)
{
	// GIVEN
	//
	// val - ��������� ��������, ��������� �� ������� �������� � �1
	// p1 - �������� ������ auto_ptr
	const int val = 10;
	auto_ptr<int> p1(new int(val));

	// WHEN
	//
	// ����������� ������� ��������� ��������� �� ���� � ���������� resource.
	// � ���������� holding_resource ��������� ��������� �� ������� ������ ������� �1
	int* resource = p1.release(), *holding_resource = p1.get();

	// THEN
	// 
	// ���������, ��� ����� ��������� ��������� ������ � ��� ������ �� ���������
	ASSERT_TRUE(holding_resource == nullptr);
	ASSERT_TRUE(*resource == val);
}

TEST(Unique_ptr, Assign_ptrs)
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
	//ASSERT_TRUE(p2.get() == default_ptr);
	//ASSERT_TRUE(p1.get() == nullptr);
}

TEST(Unique_ptr, Move_constructor)
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

TEST(Unique_ptr, Move_assignment)
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

TEST(Unique_ptr, Reset)
{
	// GIVEN
	//
	// val - ��������� ��������, ��������� �� ������� �������� � �1
	// new_val - ��������, ��������� �� ������� ����� �������� � �1 ����� ������ reset
	// p1 - �������� ������ auto_ptr
	const int val = 10, new_val = 20;
	unique_ptr<int> p1(new int(val));

	// WHEN
	//
	// ������������� ����� ������, � ������� �������� ��������� new_val
	// � ���������� curr_val ���������� ������� ��������, ������� �������� � �1
	p1.reset(new int(new_val));
	int curr_val = *p1;

	// THEN
	// 
	// ���������, ��� ����� ��������� ������ ����� ��������
	ASSERT_TRUE(curr_val == new_val);
}

TEST(Unique_ptr, Release)
{
	// GIVEN
	//
	// val - ��������� ��������, ��������� �� ������� �������� � �1
	// p1 - �������� ������ auto_ptr
	const int val = 10;
	unique_ptr<int> p1(new int(val));

	// WHEN
	//
	// ����������� ������� ��������� ��������� �� ���� � ���������� resource.
	// � ���������� holding_resource ��������� ��������� �� ������� ������ ������� �1
	int* resource = p1.release(), *holding_resource = p1.get();

	// THEN
	// 
	// ���������, ��� ����� ��������� ��������� ������ � ��� ������ �� ���������
	ASSERT_TRUE(holding_resource == nullptr);
	ASSERT_TRUE(*resource == val);
}

TEST(Shared_Ptr, Constructor)
{
	// GIVEN
	//
	// val - ��������, ��������� �� ������� �������� � ����� ���������
	const int val = 5;

	// WHEN
	//
	// ������ ����� ���������, ������� ������ �������� val
	shared_ptr<int> ip(new int(val));

	// THEN
	//
	// ���������, ��� �������� �������� ��������� � val
	ASSERT_TRUE(*ip == val);
}

TEST(Shared_Ptr, Copy_Constructor)
{
	// GIVEN
	//
	// val - ��������, ��������� �� ������� �������� � ����� ��������� ip
	// iptr - �������� ����� ���������
	const int val = 5;
	shared_ptr<int> iptr(new int(val));

	// WHEN
	//
	// ������ ��������� copy_iptr � ������� ����-������������
	// � ���������� use_count ���������� ����� ���������� �������
	shared_ptr<int> copy_iptr(iptr);
	long int use_count = copy_iptr.use_count();

	// THEN
	//
	// ���������, ��� �������� ������� ��� �������
	ASSERT_TRUE(use_count == 2);

}

TEST(Shared_Ptr, Arrow_Operator)
{
	// GIVEN
	//
	// val - ��������� ��������, ��������� �� ������� �������� � ����� ��������� ip
	// new_val - ����� ��������, ��������� �� ������� ����� ��������� � iptr
	// iptr - �������� ����� ���������
	const int val = 5, new_val = 10;
	shared_ptr<int> iptr(new int(val));

	// WHEN
	//
	// �������� ��������� �� ������ � �������� ��������� ->
	// ����������� ������� ����� ��������
	// ���������� ������� ��������, ������� �������� � ����� ���������, � ���������� curr_val
	int* temp_ptr = iptr->get_ptr();
	*temp_ptr = new_val;
	int curr_val = *iptr;

	// THEN
	//
	// ���������, ��� ������� �������� ����� �������� ������� �� ���������� � ��������� ���
	ASSERT_TRUE(curr_val == new_val);
}

TEST(Shared_Ptr, Star_Operator)
{
	// GIVEN
	//
	// val - ��������� ��������, ��������� �� ������� �������� � ����� ��������� iptr
	// iptr - �������� ����� ���������
	const int val = 5;
	shared_ptr<int> iptr(new int(val));

	// WHEN
	//
	// ���������� ������� ��������, ������� �������� � ����� ���������, � ���������� curr_val
	int curr_val = *iptr;

	// THEN
	//
	// ���������, ��� ������� �������� ����� �������� ������� �� ���������� � ��������� ���
	ASSERT_TRUE(curr_val == val);
}

TEST(Shared_Ptr, Bool_Operator)
{
	// GIVEN
	//
	// iptr - �������� ����� ���������, �������� nullptr
	shared_ptr<int> iptr;

	// WHEN
	//
	// ��������� ���������� � bool, ���������� ������ �� ��������� nullptr � ���������� is_nullptr
	bool is_nullptr = (bool)iptr;

	// THEN
	//
	// ���������, ��� iptr ������ nullptr
	ASSERT_TRUE(is_nullptr);
}

TEST(Shared_Ptr, Equal_Operator)
{
	// GIVEN
	//
	// val - ��������� ��������, ��������� �� ������� �������� � ����� ��������� iptr
	// iptr - �������� ����� ���������, �������� nullptr
	// assigned_iptr - ����� ���������, �������� nullptr, ������� ����� ���������� � �������� ������������
	const int val = 10;
	shared_ptr<int> iptr(new int(val)), assigned_iptr;

	// WHEN
	//
	// ����������� iptr ��������� assigned_iptr
	// � ���������� use_count ���������� ����� ���������� �������
	// � ���������� curr_val ���������� �������� ����������� � ���������
	assigned_iptr = iptr;
	long int use_count = iptr.use_count();
	int curr_val = *assigned_iptr;

	// THEN
	//
	// ���������, ��� ����� ���������� ����� 2 � ������� �������� ����� val
	ASSERT_TRUE(use_count == 2);
	ASSERT_TRUE(curr_val == val);
}

TEST(Shared_Ptr, Swap)
{
	// GIVEN
	//
	// val_1 - ��������, ��������� �� ������� �������� � iptr_1
	// val_2 - ��������, ��������� �� ������� �������� � iptr_2
	const int val_1 = 10, val_2 = 20;
	shared_ptr<int> iptr_1(new int(val_1)), iptr_2(new int(val_2));

	// WHEN
	//
	// ������ ������� iptr_1 � iptr_2
	// ����� �������� �������� ���������� � new_val_1 � new_val_2
	iptr_1.swap(iptr_2);
	int new_val_1 = *iptr_1, new_val_2 = *iptr_2;

	// THEN
	//
	// ���������, ��� �������� �������� ���������� �������
	ASSERT_TRUE(new_val_1 == val_2);
	ASSERT_TRUE(new_val_2 == val_1);
}

TEST(Shared_Ptr, Reset)
{
	// GIVEN
	//
	// val - ��������, ��������� �� ������� �������� � iptr
	// new_val - ����� ��������, ��������� �� ������ ����� ��������� � iptr
	const int val = 10, new_val = 20;
	shared_ptr<int> iptr(new int(val));

	// WHEN
	//
	// ����������� iptr ����� ������ �� ��������� new_val
	// ����� �������� �������� ���������� � curr_val
	iptr.reset(new int(new_val));
	int curr_val = *iptr;

	// THEN
	//
	// ���������, ��� �������� �������� ���������� �������
	ASSERT_TRUE(curr_val == new_val);
}

TEST(Shared_Ptr, Unique)
{
	// GIVEN
	//
	// val - ��������, ��������� �� ������� �������� � iptr
	const int val = 10;
	shared_ptr<int> iptr(new int(val));

	// WHEN
	//
	// ������ ������� ��������� another_owner
	// � ���������� is_unique ���������� �������� �� ������ another_owner ������������ (����������) ����������
	shared_ptr<int> iptr_another_owner(iptr);
	bool is_unique = iptr_another_owner.unique();

	// THEN
	//
	// ���������, ��� another_owner �� �������� ������������ ����������
	ASSERT_TRUE(is_unique == false);
}

TEST(Shared_Ptr, Use_count)
{
	// GIVEN
	//
	// val - ��������, ��������� �� ������� �������� � iptr
	const int val = 10;
	shared_ptr<int> iptr(new int(val));

	// WHEN
	//
	// ������ ��� ������ ������� shared_ptr, ������� ������� ��� �� ��������
	// � ���������� use_count ���������� ����� ���������� �������
	shared_ptr<int> iptr_owner_2(iptr), iptr_owner_3(iptr);
	auto use_count = iptr.use_count();

	// THEN
	//
	// ���������, ��� � ������� ��� ���������
	ASSERT_TRUE(use_count == 3);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("PAUSE");
	return 0;
}