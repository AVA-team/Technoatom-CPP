#ifndef CUSTOM_EXCEPTION_H_
#define CUSTOM_EXCEPTION_H_

#include <exception>
#include <string>

//! Macro for create custom_exception without passing previous exception object argument.
#define CUSTOM_EXCEPTION_WITHOUT_PREV(error_code, message)	\
		ava::make_custom_exc(error_code, message, __FILE__, __LINE__, std::exception());

//! Macro for create custom_exception with passing previous exception object argument.
#define CUSTOM_EXCEPTION(error_code, message, exc)			\
		ava::make_custom_exc(error_code, message, __FILE__, __LINE__, exc);

namespace ava {
	template<class PrevExceptionT>
	class custom_exception {
	public:
		//! Constructs an custom_exception object with some debug information.
		//!
		//! @param error_code number of error code.
		//! @param message string with message about error.
		//! @param filename string for name of file, where throwed exception.
		//! @param line_num number of string, where throwed exception.
		//! @param prev_exc previous throwed exception object.
		custom_exception(const int error_code, const char * message, const char * filename, const unsigned line_num, PrevExceptionT prev_exc);
		//! Constructs an custom_exception object either from another custom_exception object.
		//!
		//! @param that an custom_exception object.
		custom_exception(const custom_exception & that) noexcept;
		//! Swap all exception information with another exception.
		//!
		//! @param that an custom_exception object.
		void swap(custom_exception & that) noexcept;
		//! Copy all information from that exception.
		//!
		//! @param that An custom_exception object.
		//! @return the left-hand side custom_exception object (*this).
		custom_exception & operator= (const custom_exception & that) noexcept;
		//! @return string with message about error.
		const char * what() const noexcept;
		//! @return number of error code.
		const int error_code() const noexcept;
		//! @return string with name of file, where throwed exception.
		const char * filename() const noexcept;
		//! @return number of string, where throwed exception.
		const unsigned line_num() const noexcept;
		//! @return reference of copy previous throwed exception object.
		const PrevExceptionT & prev_exc() const noexcept;
		//! Destruct custom_exception object with all information.
		~custom_exception();
	private:
		//! number of error code.
		const int error_code_;
		//! message string with message about error.
		const std::string message_;
		//! string for name of file, where throwed exception.
		const std::string filename_;
		//! number of string, where throwed exception.
		const unsigned line_num_;
		//! copy of previous throwed exception object.
		PrevExceptionT prev_exc_;
	};

	//! Function create custom exception with autodefine previous exception type.
	//! Needed, because constructor can't autodefine template types.
	//!
	//! @return custom exception
	template<class PrevExceptionT>
	custom_exception<PrevExceptionT> make_custom_exc(const int error_code, const char * message, const char * filename, const unsigned line_num, PrevExceptionT prev_exc) {
		return custom_exception<PrevExceptionT>(error_code, message, filename, line_num, prev_exc);
	}
}

#include "implementation/custom_exception_implementation.h"

#endif //CUSTOM_EXCEPTION_H_
