#ifndef CUSTOM_EXCEPTION_IMPLEMENTATION_H_
#define CUSTOM_EXCEPTION_IMPLEMENTATION_H_

#include <algorithm>

namespace ava {
  template<class PrevExceptionT>
  custom_exception<PrevExceptionT>::custom_exception(const int error_code, const char * message, const char * filename, const unsigned line_num, PrevExceptionT prev_exc) :
      error_code_(error_code), message_(message), filename_(filename), line_num_(line_num), prev_exc_(prev_exc) {}

  template<class PrevExceptionT>
  custom_exception<PrevExceptionT>::custom_exception(const custom_exception & that) noexcept :
	  error_code_(that.error_code_), message_(that.message_), filename_(that.filename_), line_num_(that.line_num_), prev_exc_(that.prev_exc_) {}
  
  template<class PrevExceptionT>
  void custom_exception<PrevExceptionT>::swap(custom_exception & that) noexcept {
	  std::swap(error_code_, that.error_code_);
	  std::swap(message_, that.message_);
	  std::swap(filename_, that.filename_);
	  std::swap(line_num_, that.line_num_);
	  std::swap(prev_exc_, that.prev_exc_);
  }

  template<class PrevExceptionT>
  custom_exception<PrevExceptionT> & custom_exception<PrevExceptionT>::operator= (const custom_exception & that) noexcept {
	  if (this != &that) {
		  custom_exception tmp_exception(that);
		  swap(tmp_exception);
	  }
	  return *this;
  }

  template<class PrevExceptionT>
  const char * custom_exception<PrevExceptionT>::what() const noexcept {
	  return message_.c_str();
  }

  template<class PrevExceptionT>
  const int custom_exception<PrevExceptionT>::error_code() const noexcept {
	  return error_code_;
  }

  template<class PrevExceptionT>
  const char * custom_exception<PrevExceptionT>::filename() const noexcept {
	  return filename_.c_str();
  }

  template<class PrevExceptionT>
  const unsigned custom_exception<PrevExceptionT>::line_num() const noexcept {
	  return line_num_;
  }

  template<class PrevExceptionT>
  const PrevExceptionT & custom_exception<PrevExceptionT>::prev_exc() const noexcept {
	  return prev_exc_;
  }

  template<class PrevExceptionT>
  custom_exception<PrevExceptionT>::~custom_exception() {}
}

#endif
