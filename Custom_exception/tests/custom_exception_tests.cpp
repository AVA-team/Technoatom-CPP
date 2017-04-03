#include "../custom_exception.h"
#include <iostream>

using std::cout;

int main() {

	auto ex = CUSTOM_EXCEPTION_WITHOUT_PREV(1, "MESS1");
	cout << ex.error_code() << " " << ex.what() << " " << ex.filename() << " " << ex.line_num() << " " << ex.prev_exc().what() << std::endl;

	auto ex2 = CUSTOM_EXCEPTION(2, "MESS2", ex);
	cout << ex2.error_code() << " " << ex2.what() << " " << ex2.filename() << " " << ex2.line_num() << " " << ex2.prev_exc().what() << std::endl;

	try {
		throw CUSTOM_EXCEPTION_WITHOUT_PREV(1, "CUSTOM EXCEPTION!");
	}
	catch (ava::custom_exception<std::exception> & ex) {
		cout << ex.error_code() << " " << ex.what() << std::endl;
	}

	system("PAUSE");
	return 0;
}