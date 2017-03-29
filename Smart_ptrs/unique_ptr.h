#ifndef _UNIQUE_PTR_H
#define _UNIQUE_PTR_H

namespace ava {
	template<class T>
	class unique_ptr {
	public:
		//! Constructs an unique_ptr object either from a pointer.
		//!
		//! @param p Pointer to an object of type T, which is the unique_ptr's template parameter.
		explicit unique_ptr(T* p = nullptr);
		//! Copy-constructor is depricated
		unique_ptr(const unique_ptr& that) = delete;
		//! Move constructor
		unique_ptr(unique_ptr&& that);
		//! Destruct an object pointed by ptr_
		~unique_ptr();
		//! Assigned operator is depricated
		unique_ptr& operator=(const unique_ptr& that) = delete;
		//! Move assigned operator
		unique_ptr& operator=(unique_ptr&& that);
		//! Returns a reference to the value pointed by the auto_ptr object.
		//! The unique_ptr object must point to some object (must not be a null pointer) in order to be dereferenciable.
		//!
		//! @return A reference to the element pointed by the unique_ptr object.
		T & operator*();
		//! Returns the element pointed by the unique_ptr object in order to access one of its members.
		//!
		//! @return A pointer to the element pointed by the unique_ptr object.
		T* operator->();
		//! Returns internal pointer
		T* get() const;
		//! Returns whether an object is currently managed by the unique_ptr (i.e., whether the unique_ptr is not empty).
		explicit operator bool() const;
		//! Releases ownership of its stored pointer, by returning its value and replacing it with a null pointer.
		T* release();
		//! Destroys the object currently managed by the unique_ptr (if any) and takes ownership of p.
		void reset(T* p = nullptr);
		//! Exchanges the contents of the unique_ptr object with those of x, transferring ownership of any managed object between them without destroying either
		void swap(unique_ptr<T>& that);
	private:
		//! A pointer to the element pointed by the auto_ptr object.
		T* ptr_;
	};
}

#include "unique_ptr_implementation.h"

#endif // _UNIQUE_PTR_H
