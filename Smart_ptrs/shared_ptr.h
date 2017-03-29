#ifndef _SHARED_PTR_H_
#define _SHARED_PTR_H_

namespace ava {
	template<class T>
	class shared_ptr {
	public:
		//! Constructs an object with pointer p
		//!
		//! @param p is a pointer to an object that is stored in the current object
		shared_ptr(T* p = nullptr);
		//! Constructs an object with another object
		//! 
		//! @param that is another object that is constructed from
		shared_ptr(const shared_ptr<T>& that);
		//! Destructs object
		~shared_ptr();
		class Proxy {
		public:
			Proxy(T* p = nullptr);
			~Proxy();
			T* operator->();
			void increment_count();
			void decrement_count();
			long int get_count() const;
			T* get_ptr() const;

		private:
			long int count_;
			T* ptr_;
		};
		Proxy* operator->() const;
		T& operator*();
		explicit operator bool() const;
		const shared_ptr<T>& operator=(const shared_ptr<T>& that);
		void swap(shared_ptr& that);
		void reset(T* p = nullptr);
		T* get() const;
		long int use_count() const;
		bool unique() const;

	private:
		Proxy* proxy_ptr_;
	};
}

#include "shared_ptr_implementation.h"

#endif
