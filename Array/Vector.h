#ifndef VECTOR_H_
#define VECTOR_H_

#include "Container_interface.h"

namespace ava {
	//! Initial capacity of vector, if constuct it with default constuctor.
	const std::size_t standart_init_capacity = 10;

	//! Array with elements in dynamic memory.
	template <class T>
	class Vector : public ContainerInterface<T> {
	public:
		explicit Vector(const std::size_t capacity = standart_init_capacity);
		explicit Vector(const Vector & that);
		//! Fill constructor constucts a container with n elements.
		//! Each element is a copy of value
		//! 
		//! @param value is a value that equal to each element in the created container
		explicit Vector(std::size_t size, const T& value);
		~Vector() {
			clear();
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
			std::swap(capacity_, that.capacity_);
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
			if (size_ == 0) {
				throw std::length_error("Try to pop from empty vector!");
			}
			--size_;
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
			data_ = nullptr;
			size_ = 0;
		}
	private:
		const std::size_t CAPACITY_INCREMENT;
		std::size_t capacity_;
	};
#include "implementation\Vector_implementation.h"
}

#endif VECTOR_H_
