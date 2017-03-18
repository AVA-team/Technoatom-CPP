#ifndef CONTAINER_INTERFACE_H_
#define CONTAINER_INTERFACE_H_

#include <string>

namespace ava {
	template <class T>
	class ContainerInterface {
	public:
		//! Forward iterator for work with static and dinamic arrays.
		class ArrayIterator
			: public std::iterator<std::forward_iterator_tag, T>
		{
		public:
			ArrayIterator(T* val_p);
			~ArrayIterator();
			T& operator*();
			T* operator->();
			ArrayIterator& operator++();
			ArrayIterator& operator--();
			ArrayIterator operator++(int);//postfix
			ArrayIterator operator--(int);//postfix
			bool operator==(const ArrayIterator& other);
			bool operator!=(const ArrayIterator& other);
		private:
			T* val_p_;
		};
		//! Constructor for operate with Static Array and Dynamic Vector with same Interface
		ContainerInterface(T * data, std::size_t size);

		//! Returns a reference to the element at specified location pos. No bounds checking is performed.
		//!
		//! @param pos is position of the element to return
		//! @return reference of the element to return
		virtual const T & operator[](const std::size_t pos) const;

		//! Returns a reference to the element at specified locationpos,
		//! with bounds checking.
		//! If pos is not within the range of the array,
		//! an exception of type std::out_of_range is thrown.
		//!
		//! @param pos is position of the element to return
		//! @throw std::out_of_range if !(pos < size())
		//! @return reference of the element to return
		virtual T & at(const std::size_t pos) const;

		//! Returns a reference to the first element in the array.
		//! Calling front on an empty array is undefined.
		//!
		//! @return reference to the first element
		virtual T & front() const;

		//! Returns a reference to the last element in the array.
		//! Calling back on an empty array is undefined.
		//!
		//! @return reference to the last element
		virtual T & back() const;

		//! Returns pointer to the underlying array serving as element storage.
		//! The pointer is such that range
		//! [data(); data() + size()) is always a valid range,
		//! even if the array is empty
		//! (data() is not dereferenceable in that case).
		//!
		//! @return pointer to the underlying element storage
		virtual T * data() const;

		//! Checks if the array has no elements.
		//!
		//! @return true if the array is empty, false otherwise
		virtual bool empty() const;

		//! Returns the number of elements in the array.
		//!
		//! @return the number of elements in the array
		virtual std::size_t size() const;

		//! Assigns the given value value to all elements in the array.
		//!
		//! @param value is the value to assign to the elements
		virtual void fill(const T & value);

		//! Present array in console.
		virtual void dump() const;

		//! Returns iterator that points to the first element
		virtual ArrayIterator begin();

		//! Returns iterator that points to the end element
		virtual ArrayIterator end();
	protected:
		//! Out of range exception text.
		static const std::string OUT_OF_RANGE_EXC_TEXT;
		T * data_;
		std::size_t size_;
	private:
		ContainerInterface();
		ContainerInterface(const ContainerInterface & that);
		const ContainerInterface & operator=(const ContainerInterface & that);
	};
#include "implementation\container_interface.hpp"
}

#endif //CONTAINER_INTERFACE_H_
