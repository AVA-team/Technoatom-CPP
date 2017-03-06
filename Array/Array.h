#ifndef ARRAY_H_
#define ARRAY_H_

#include <string>

namespace ava {

	template <class T, class ContainerType>
	class ArrayInterface {
	public:
		//! Constructor for operate with Static Array and Dynamic Vector with same Interface
		ArrayInterface(ContainerType & container);

		//! Returns a reference to the element at specified location pos. No bounds checking is performed.
		//!
		//! @param pos is position of the element to return
		//! @return reference of the element to return
		virtual T & operator[](const std::size_t pos) const;

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

	protected:
		//! Out of range exception text.
		static const std::string OUT_OF_RANGE_EXC_TEXT;
		ContainerType & container_;
	private:
		ArrayInterface();
		ArrayInterface(const ArrayInterface & that);
		const ArrayInterface & operator=(const ArrayInterface & that);
	};

	//! Array with elements in dynamic memory.
	template <class T>
	class Vector : public ArrayInterface<T, Vector<T>> {
	public:
		friend ArrayInterface;
		explicit Vector(const std::size_t size = 2);
		Vector(const Vector & that);
		~Vector();
		const Vector & operator=(const Vector & that);

		//! Exchanges the contents of the array with those of other.
		//! Does not cause references to associate with the other array.
		//!
		//! @param that is array to exchange the contents with
		void swap(Vector & that);

	private:
		//! Size of dynamic array.
		 std::size_t size_;
		//! Pointer to data.
		T * data_;
	};


	//! Array with elements in static memory.
	template <class T, std::size_t N>
	class Array : public ArrayInterface<T, Array<T,N>> {
	public:
		friend ArrayInterface;
		Array() ;
		Array(const Array & that) ;
		~Array();
		const Array & operator=(const Array & that);

		//! Exchanges the contents of the array with those of other.
		//! Does not cause references to associate with the other array.
		//!
		//! @param that is array to exchange the contents with
		void swap(Array & that);

	private:
		//! Size of static array.
		std::size_t size_;
		//! Data array.
		T data_[N];
	};

#include "Array_interface_realization.h"
#include "Vector_realization.h"
#include "Array_realization.h"


}
#endif // ARRAY_H_
