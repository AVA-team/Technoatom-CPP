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
		//! Class for indirect acess to a resource
		class Proxy {
		public:
			//! Construct Proxy object with resource pointer
			//!
			//! @param p is a resource pointer
			Proxy(T* p = nullptr);
			//! Destroy resource
			~Proxy();
			//! Overloaded arrow operator to acess to the resource
			T* operator->();
			//! Increment amount of the resource users
			void increment_count();
			//! Decrement amount of the resource users
			void decrement_count();
			//! Return amount of the resource users
			long int get_count() const;
			//! Return pointer to the resource
			T* get_ptr() const;

		private:
			long int count_;
			T* ptr_;
		};
		//! Overloaded arrow operator return pointer to the Proxy object which store a resource object
		Proxy* operator->() const;
		//! Overloaded star operator returns reference to the resource
		T& operator*();
		//! Overloded bool conversation to check if current holding resource is a nullptr
		explicit operator bool() const;
		//! Overloaded assignment operator
		//!
		//! @param that is another shared_ptr object that is assigned from
		const shared_ptr<T>& operator=(const shared_ptr<T>& that);
		//! Swap content of this and that shared_ptr objects
		//!
		//! @param that is another shared_ptr object
		void swap(shared_ptr& that);
		//! Reset content of this object
		//! 
		//! @param p is another resource pointer
		void reset(T* p = nullptr);
		//! Returns resource pointer
		T* get() const;
		//! Returns amount of resource users
		long int use_count() const;
		//! Checks if there is only one resource user
		bool unique() const;

	private:
		Proxy* proxy_ptr_;
	};
}

#include "shared_ptr_implementation.h"

#endif
