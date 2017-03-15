#ifndef VECTOR_REALIZATION_H_
#define VECTOR_REALIZATION_H_
#include<exception>
#include<algorithm>

template <class T>
Vector<T>::Vector(std::size_t capacity = standart_init_capacity):
  size_(0),
  CAPACITY_INCREMENT(10U),
  capacity_(capacity),
  data_(new T[capacity_]),
  ArrayInterface(*this){ }


template <class T>
Vector<T>::Vector(const Vector & that) :
	size_(that.size_),
	CAPACITY_INCREMENT(10U),
	capacity_(that.capacity_),
	data_(new T[that.capacity_]),
	ArrayInterface(*this) {

	std::copy(that.data_, that.data_ + size_, data_);
}


template<class T>
Vector<T>::Vector(std::size_t size, const T& value) :
	size_(size),
	CAPACITY_INCREMENT(10U),
	capacity_(size_ + CAPACITY_INCREMENT),
	data_(new T[capacity_]),
	ArrayInterface(*this) {

	for (size_t i = 0; i < size_; i++)
	{
		data_[i] = value;
	}
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
void Vector<T>::insert(std::size_t pos, std::size_t elements_count, const T& value_to_copy) {

	if (pos > size_) throw std::out_of_range("Failed attempt to invoke method Vector<T>::insert()\nIndex (pos) bigger than current size\n");

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
		reserve(new_size + CAPACITY_INCREMENT);
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
		capacity_ = size_ + CAPACITY_INCREMENT;
		delete[] data_;
		data_ = new T[capacity_];
	}
	for (std::size_t i = 0; i < size_; i++)
	{
		data_[i] = value_to_copy;
	}
}


;
#endif // VECTOR_REALIZATION_H_