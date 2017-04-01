#pragma once

#include"array.h"

namespace ava {

	template <class T, std::size_t N>
	Array<T, N>::Array() :
		ContainerInterface(static_data_, 0) {
	}


	template <class T, std::size_t N>
	Array<T, N>::Array(const Array & that) :
		ContainerInterface(static_data_, that.size_) {
		for (std::size_t i = 0; i < size_; i++) {
			data_[i] = that.data_[i];
		}
	}


	template <class T, std::size_t N>
	Array<T, N>::~Array() {}


	template <class T, std::size_t N>
	const Array<T, N> & Array<T, N>::operator=(const Array & that) {
		if (this == &that) {
			return *this;
		}
		Array<T, N> tmp_array(that);
		swap(tmp_array);
		return *this;
	}


	template<class T, std::size_t N>
	T& Array<T, N>::operator[](const std::size_t pos) {
		if (pos >= N) {
			throw std::length_error("Failed attempt to invoke Array<T,N>::operator[](const size_t pos). pos is bigger or equal than N\n");
		}
		if (pos >= size_) {
			size_ = pos + 1;
		}
		return static_data_[pos];
	}


	template <class T, std::size_t N>
	void Array<T, N>::swap(Array & that) {
		std::swap(static_data_, that.static_data_);
	}


	template<class T, std::size_t N>
	void Array<T, N>::fill(const T& val) {
		for (std::size_t i = 0; i < N; i++) {
			static_data_[i] = val;
		}
		size_ = N;
	}

}