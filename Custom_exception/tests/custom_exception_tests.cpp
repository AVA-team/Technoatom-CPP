#include "../custom_exception.h"
#include <iostream>
#include "gtest\gtest.h"

using std::cout;

class GTest_Object_For_Testing_Custom_Exceptions : public testing::Test
{
public:
	//! Function to throw custom exception without previous specialization
	void inner_throwing_func() {
		num_str_throwed_inner = __LINE__ + 1;
		throw CUSTOM_EXCEPTION_WITHOUT_PREV(error_code_inner, exception_message_inner);
	}
	//! Function to throw custom exception with previous exception param specialization of inner_throwing_func() exception.
	void outer_throwing_func() {
		try {
			inner_throwing_func();
		}
		catch (ava::custom_exception<std::exception> & exc) {
			num_str_throwed_outer = __LINE__ + 1;
			throw CUSTOM_EXCEPTION(error_code_outer, exception_message_outer, exc);
		}

	}
protected:
	const int error_code_outer = 1;
	const int error_code_inner = 2;
	const char * exception_message_outer = "outer exception";
	const char * exception_message_inner = "inner exception";
	unsigned num_str_throwed_outer;
	unsigned num_str_throwed_inner;
};

TEST_F(GTest_Object_For_Testing_Custom_Exceptions, Inner_exception_testing)
{
	// GIVEN
	//
	// GTest_Object_For_Testing_Custom_Exceptions - object for testing custom exceptions

	// WHEN
	//
	// Call inner_throwing_func().
	try {
		inner_throwing_func();
	}
	// THEN
	//
	// Check that throwed exception is of the correct type and with right information of throwed exception.
	catch (ava::custom_exception<std::exception> & exc) {
		ASSERT_EQ(exc.error_code(), error_code_inner);
		ASSERT_STREQ(exc.what(), exception_message_inner);
		ASSERT_STREQ(exc.filename(), __FILE__);
		ASSERT_EQ(exc.line_num(), num_str_throwed_inner);
	}
}

TEST_F(GTest_Object_For_Testing_Custom_Exceptions, Outer_exception_testing)
{
	// GIVEN
	//
	// GTest_Object_For_Testing_Custom_Exceptions - object for testing custom exceptions

	// WHEN
	//
	// Call outer_throwing_func().
	try {
		outer_throwing_func();
	}
	// THEN
	//
	// Check that throwed exception is of the correct type and with right information of throwed exception and inner exception.
	catch (ava::custom_exception<ava::custom_exception<std::exception>> & exc) {
		ASSERT_EQ(exc.error_code(), error_code_outer);
		ASSERT_STREQ(exc.what(), exception_message_outer);
		ASSERT_STREQ(exc.filename(), __FILE__);
		ASSERT_EQ(exc.line_num(), num_str_throwed_outer);

		ASSERT_EQ(exc.prev_exc().error_code(), error_code_inner);
		ASSERT_STREQ(exc.prev_exc().what(), exception_message_inner);
		ASSERT_STREQ(exc.prev_exc().filename(), __FILE__);
		ASSERT_EQ(exc.prev_exc().line_num(), num_str_throwed_inner);
	}
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("PAUSE");
	return 0;
}