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
		explicit Vector(const Vector & that);

		//! Fill constructor constucts a container with n elements.
		//! Each element is a copy of value
		//! 
		//! @param value is a value that equal to each element in the created container
		explicit Vector(std::size_t size, const T& value);

		~Vector() {

			delete[] data_;
			data_ = nullptr;
		}

		const Vector & operator=(const Vector & that) {

			Vector<T> tmp_vector(that);
			swap(tmp_vector);
			return *this;
		}

		//! Exchanges the contents of the array with those of other.
		//! Does not cause references to associate with the other array.
		//!
		//! @param that is array to exchange the contents with
		void swap(Vector & that) {

			std::swap(size_, that.size_);
			std::swap(data_, that.data_);
		}

		//! Adds a new element at the end of the vector, after its current last element.
		//! The content of val is copied (or moved) to the new element.
		//! This effectively increases the container size by one,
		//! which causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
		//!
		//! @param value is a new value to push in back
		void push_back(T value_to_copy);

		//! Delete last element.
		//! Removes the last element in the vector, effectively reducing the container size by one.
		//! This destroys the removed element.
		void pop_back() {

			if (size_ == 0) return;

			delete data_[--size_];
		}

		//! The vector is extended by inserting new elements before the element at the specified position, effectively increasing the container size by the number of elements inserted.
		void insert(std::size_t pos, std::size_t elements_count, const T& value_to_copy);

		//! Resizes the container so that it contains new_size elements.
		//! If new size is smaller than the current container size, the content is reduced to its first new_size elements, removing those beyond (and destroying them).
		//! If new size is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of new_size.
		//! If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
		//! If new size is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
		//! Notice that this function changes the actual content of the container by inserting or erasing elements from it.
		//!
		//! @param new_size is a new size for a vector
		//! @param value_to_copy is a value that will be copied to each new elements in data sotrage if new size is greater than current size
		void resize(std::size_t new_size, T value_to_copy = T());

		//! Requests that the vector capacity be at least enough to contain new_capacity elements.
		//! If new capacity is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to new capacity (or greater).
		//! In all other cases, the function call does not cause a reallocation and the vector capacity is not affected
		//! This function has no effect on the vector size and cannot alter its elements.
		//! 
		//! @param new_capacity is a new capacity for the current vector
		void reserve(std::size_t new_capacity);

		//! Requests the container to reduce its capacity to fit its size.
		//! This may cause a reallocation, but has no effect on the vector size and cannot alter its elements.
		void shrink_to_fit();

		//! Returns capacity of the current vector
		std::size_t capacity() const { return capacity_; }

		//! Assign vector content.
		//! Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
		void assign(std::size_t count, const T& value_to_Copy);

		//! Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
		void clear() {
			delete[] data_;
			size_ = 0;
		}
	private:
		//! Size of dynamic array.
		 std::size_t size_;
		const std::size_t CAPACITY_INCREMENT;
		std::size_t capacity_;
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
