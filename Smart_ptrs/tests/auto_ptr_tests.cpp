#include <iostream>
#include "..\auto_ptr.h"
#include "gtest\gtest.h"

using ava::auto_ptr;

TEST(auto_ptr, Assign_ptrs)
{
	//GIVEN
	auto_ptr<int> p1(new int(1));
	int * default_ptr = p1.get();
	//WHEN
	auto_ptr<int> p2;
	p2 = p1;
	//THEN
	ASSERT_TRUE(p2.get() == default_ptr);
	ASSERT_TRUE(p1.get() == nullptr);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("PAUSE");
	return 0;
}