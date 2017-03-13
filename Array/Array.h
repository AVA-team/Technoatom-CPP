#ifndef ARRAY_H_
#define ARRAY_H_

#include "Array_interface.h"

namespace ava {
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



#include "Array_realization.h"


}
#endif // ARRAY_H_
