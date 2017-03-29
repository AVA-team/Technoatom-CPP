#ifndef AUTO_PTR_H_
#define AUTO_PTR_H_

namespace ava {
	template<class T>
	class auto_ptr {
	private:
		T * ptr_;
	public:
		explicit auto_ptr(T * p = nullptr);
		auto_ptr(auto_ptr & that);
		~auto_ptr();
		T * get() const;
		T & operator*() const;
		T * operator->() const;
		auto_ptr & operator=(auto_ptr& that);
		T * release();
		void reset(T * p = nullptr);
	};
}

#include "implementation/auto_ptr_implementation.h"

#endif //AUTO_PTR_H_