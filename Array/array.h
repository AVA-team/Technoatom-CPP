#ifndef ARRAY_H_
#define ARRAY_H_

#include "container_interface.h"

namespace ava {
	//! Array with elements in static memory.
	template <class T, std::size_t N>
	class Array : public ContainerInterface<T> {
	public:
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
		//! Data array.
		T static_data_[N];
	};
#include "implementation\array.hpp"
}
#endif // ARRAY_H_
