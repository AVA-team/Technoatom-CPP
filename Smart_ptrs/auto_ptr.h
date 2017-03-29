#ifndef AUTO_PTR_H_
#define AUTO_PTR_H_

namespace ava {
	template<class T>
	class auto_ptr {
	private:
		T * ptr_;
	public:
		//! Constructs an auto_ptr object either from a pointer.
		//!
		//! @param p Pointer to an object of type T, which is the auto_ptr's template parameter.
		explicit auto_ptr(T * p = nullptr);
		//! Constructs an auto_ptr object either from another auto_ptr object.
		//!
		//! @param that An auto_ptr object. Ownership is taken from it, therefore, a releases it.
		auto_ptr(auto_ptr & that);
		//! Deallocates the block of memory the object "points to" using delete (delete get()) and destructs the object.
		~auto_ptr();
		//! Returns a pointer to the object pointed by the auto_ptr object, if any, or zero if it does not point to any object.
		//!
		//! @return A pointer to the element pointed by the auto_ptr object.
		T * get() const;
		//! Returns a reference to the value pointed by the auto_ptr object.
		//! The auto_ptr object must point to some object (must not be a null pointer) in order to be dereferenciable.
		//!
		//! @return A reference to the element pointed by the auto_ptr object.
		T & operator*() const;
		//! Returns the element pointed by the auto_ptr object in order to access one of its members.
		//!
		//! @return A pointer to the element pointed by the auto_ptr object.
		T * operator->() const;
		//! Copies the value of the pointer held by that.
		//! The object on the left-hand side takes ownership of the pointer (i.e., it is now in charge of freeing the memory block when destroyed). 
		//! Therefore, the auto_ptr object on the right-hand side is automatically released (i.e., it is set to point to the null pointer) after the copy.
		//! If the (left-hand side) object was being used to point to an object before the operation, the pointed object is destroyed (by calling operator delete).
		//!
		//! @param that An auto_ptr object.
		//! @return The left-hand side auto_ptr object (*this).
		auto_ptr & operator=(auto_ptr& that);
		//! Sets the auto_ptr internal pointer to null pointer (which indicates it points to no object) without destructing the object currently pointed by the auto_ptr.
		//!
		//! @return A pointer to the element pointed by the auto_ptr object before the call. After the call, the internal pointer's value is the null pointer (points to no object).
		T * release();
		//! Destructs the object pointed by the auto_ptr object, if any, and deallocates its memory (by calling operator delete). 
		//! If a value for p is specified, the internal pointer is initialized to that value (otherwise it is set to the null pointer).
		//!
		//! @param p Pointer to element. Its value is set as the new internal pointer's value for the auto_ptr object.
		void reset(T * p = nullptr);
	};
}

#include "implementation/auto_ptr_implementation.h"

#endif //AUTO_PTR_H_