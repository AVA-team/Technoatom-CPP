#pragma once

#include "vector.h"

namespace ava {

	const size_t CAPACITY_INCREMENT_VALUE = 10U;

	template <class T>
	Vector<T>::Vector(std::size_t capacity = default_capacity) :
		ContainerInterface(new T[capacity], 0),
		CAPACITY_INCREMENT(CAPACITY_INCREMENT_VALUE),
		capacity_(capacity) { }


	template <class T>
	Vector<T>::Vector(const Vector& that) :
		ContainerInterface(new T[that.capacity_], that.size_),
		CAPACITY_INCREMENT(CAPACITY_INCREMENT_VALUE),
		capacity_(that.capacity_) {
		std::copy(that.data_, that.data_ + size_, data_);
	}


	template<class T>
	Vector<T>::Vector(const std::initializer_list<T>& init) :
		ContainerInterface(new T[init.size()], init.size()),
		CAPACITY_INCREMENT(CAPACITY_INCREMENT_VALUE),
		capacity_(size_) {
		int i = 0;
		for (auto it = init.begin(); it != init.end(); ++it, ++i) {
			data_[i] = *it;
		}
	}


	template<class T>
	Vector<T>::Vector(Vector&& that) :
		ContainerInterface(nullptr, 0),
		CAPACITY_INCREMENT(CAPACITY_INCREMENT_VALUE),
		capacity_(0) {
		std::cout << "Hi from move constructor. Temprory object: 0x" << &that << ". this: 0x" << this << std::endl;
		swap(that);
	}


	template<class T>
	Vector<T>::~Vector() {
		clear();
	}


	template<class T>
	const Vector<T>& Vector<T>::operator=(const Vector<T>& that) {
		Vector<T> tmp_vector(that);
		swap(tmp_vector);
		return *this;
	}


	template<class T>
	Vector<T>& Vector<T>::operator=(Vector<T>&& that) {
		std::cout << "Hi from move assignment. Temprory object: 0x" << &that << ". this: 0x" << this << std::endl;
		swap(that);
		return *this;
	}


	template<class T>
	Vector<T>::Vector(std::size_t size, const T& value) :
		ContainerInterface(nullptr, size),
		CAPACITY_INCREMENT(CAPACITY_INCREMENT_VALUE),
		capacity_(size) {
		data_ = new T[capacity_];
		for (size_t i = 0; i < size_; i++) {
			data_[i] = value;
		}
	}


	template<class T>
	T& Vector<T>::operator[](const std::size_t pos) {
		if (pos < capacity_ && pos >= size_) {
			size_ = pos + 1;
		}
		else {
			std::size_t new_capacity = get_proper_new_capacity(pos + 1);
			reserve(new_capacity);
			size_ = pos + 1;
		}
		return data_[pos];
	}


	template<class T>
	bool Vector<T>::operator==(const Vector<T>& that) {
		bool are_equal = (size_ == that.size_) && (capacity_ == that.capacity_);
		if (are_equal) {
			for (std::size_t i = 0; i < size_; i++)
			{
				are_equal = are_equal && (data_[i] == that.data_[i]);
				if (!are_equal) {
					break;
				}
			}
		}
		return are_equal;
	}


	template<class T>
	bool Vector<T>::operator!=(const Vector<T>& that) {
		return !(*this == that);
	}


	template<class T>
	void Vector<T>::swap(Vector<T>& that) {
		std::swap(capacity_, that.capacity_);
		std::swap(size_, that.size_);
		std::swap(data_, that.data_);
	}


	template<class T>
	void Vector<T>::push_back(T value_to_copy) {
		std::size_t new_size = size_ + 1;
		if (new_size > capacity_) {
			reserve(capacity_ + CAPACITY_INCREMENT);
		}
		data_[size_++] = value_to_copy;
	}


	template<class T>
	void Vector<T>::pop_back() {
		if (size_ == 0) {
			throw std::length_error("Attempt to pop from empty vector!");
		}
		--size_;
	}


	template<class T>
	void Vector<T>::insert(std::size_t pos, std::size_t elements_count, const T& value_to_copy) {
		if (pos > size_) {
			throw std::out_of_range("Failed attempt to invoke method Vector<T>::insert()\nIndex (pos) bigger than current size\n");
		}
		const std::size_t new_size = (size_ + elements_count);
		const std::size_t new_elemets_end = pos + elements_count;
		if (new_size > capacity_) {
			capacity_ = new_size + CAPACITY_INCREMENT;
			auto new_data = new T[capacity_];
			std::copy(begin(), end(), new_data);
			delete[] data_;
			data_ = new_data;
		}
		std::copy_backward(data_ + pos, data_ + size_, data_ + new_size);
		for (std::size_t i = pos; i < new_elemets_end; i++) {
			data_[i] = value_to_copy;
		}
		size_ = new_size;
	}


	template<class T>
	void Vector<T>::resize(std::size_t new_size, T value_to_copy = T()) {
		if (new_size == size_) return;
		if (new_size > capacity_) {
			reserve(get_proper_new_capacity(new_size));
		}
		for (size_t i = size_; i < new_size; i++) {
			data_[i] = value_to_copy;
		}
		size_ = new_size;
	}


	template<class T>
	void Vector<T>::reserve(std::size_t new_capacity) {
		if (new_capacity <= capacity_) return;
		else {
			capacity_ = new_capacity;
			auto new_data = new T[capacity_];
			std::copy(begin(), end(), new_data);
			delete[] data_;
			data_ = new_data;
		}
	}


	template<class T>
	void Vector<T>::shrink_to_fit() {
		capacity_ = size_;
		auto new_data = new T[capacity_];
		std::copy(begin(), end(), new_data);
		delete[] data_;
		data_ = new_data;
	}


	template<class T>
	void Vector<T>::assign(std::size_t count, const T& value_to_copy) {
		size_ = count;
		if (count > capacity_) {
			capacity_ = get_proper_new_capacity(count);
			delete[] data_;
			data_ = new T[capacity_];
		}
		for (std::size_t i = 0; i < size_; i++) {
			data_[i] = value_to_copy;
		}
	}


	template<class T>
	void Vector<T>::clear() {
		delete[] data_;
		data_ = nullptr;
		size_ = 0;
	}


	template<class T>
	std::size_t Vector<T>::get_proper_new_capacity(std::size_t new_size) {
		if (new_size <= capacity_) {
			return capacity_;
		}
		std::size_t amount_of_increment = ( (new_size - capacity_) / CAPACITY_INCREMENT ) + 1;
		return capacity_ + amount_of_increment * CAPACITY_INCREMENT;
	}

}