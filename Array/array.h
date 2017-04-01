#pragma once

#include "implementation/container_interface.hpp"

namespace ava {
	//! Array with elements in static memory.
	template <class T, std::size_t N>
	class Array : public ContainerInterface<T> {
	public:

		Array();

		Array(const Array & that);

		~Array();

		//! Overloading assignment operator
		//!
		//! @param that is an array which is assigned from
		const Array & operator=(const Array & that);
		T& operator[](const std::size_t pos);

		//! Exchanges the contents of the array with those of other.
		//! Does not cause references to associate with the other array.
		//!
		//! @param that is array to exchange the contents with
		void swap(Array & that);
		//! Assigns the given value value to all elements in the array.
		//!
		//! @param value is the value to assign to the elements
		void fill(const T & value) override;
	private:
		//! Data array.
		T static_data_[N];
	};
}
