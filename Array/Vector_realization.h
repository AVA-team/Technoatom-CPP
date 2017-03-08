#ifndef VECTOR_REALIZATION_H_
#define VECTOR_REALIZATION_H_
#include<exception>

template <class T>
Vector<T>::Vector(std::size_t capacity):
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

	for (std::size_t i = 0; i < size_; i++) {
		data_[i] = that[i];
	}
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
	if (new_size <= capacity_) {
		data_[size_++] = value_to_copy;
	}
	else {
		T temp_buffer[size_];
		std::copy(data_, data_ + size_, temp_buffer);
		capacity_ += CAPACITY_INCREMENT;
		size_++;
		delete[] data_;
		data_ = new T[capacity_];
		for (std::size_t i = 0; i < (size_ - 1); i++)
		{
			data_[i] = temp_buffer[i];
		}
		data[size_ - 1] = value_to_copy;
		
	}
}


template<class T>
void Vector<T>::insert(std::size_t pos, std::size_t elements_count, const T& value_to_copy) {

	if (pos > size_) throw std::out_of_range("Failed attempt to invoke method Vector<T>::insert()\nIndex (pos) bigger than current size\n");

	std::size_t new_size = (size_ + elements_count);
	if (new_size < capacity_) {
		if (pos == size_) {
			for (std::size_t i = size_; i < new_size; i++) {
				data_[i] = value_to_copy;
			}
		}
		else {
			std::size_t buffer_length = size_ - pos;
			T temp_buffer[buffer_length];
			for (std::size_t i = 0; i < buffer_length; i++) {
				temp_buffer[i] = data_[pos + i]
			}
			std::size_t i = pos
			for (; i < elements_count; i++) {
				data_[i] = value_to_copy;
			}
			for (; i < new_size; i++) {
				data_[i] = temp_buffer[i - elements_count - pos];
			}
		}
	}
	else {
		capacity_ = new_size + CAPACITY_INCREMENT;
		T temp_buffer[size_];
		std::copy(data_, data_ + size_, temp_buffer);
		clear();
		data_ = new T[capacity_];
		for (std::size_t i = 0; i < new_size; i++) {
			if (i < pos) {
				data_[i] = temp_buffer[i];
			}
			else if (i < (pos + elements_count)) {
				data_[i] = value_to_copy;
			}
			else {
				data_[i] = temp_buffer[i - elements_count];
			}
		}
	}
	size_ = new_size;
}


template<class T>
void Vector<T>::resize(std::size_t new_size, T value_to_copy = T()) {

	if (new_size == size_) return;

	if (new_size > capacity_) {
		T temp_buffer[size_];
		std::copy(data_, data_ + size_, temp_buffer);
		capacity_ = new_size + CAPACITY_INCREMENT;
		delete[] data_;
		data_ = new T[capacity_];
		for (std::size_t i = 0; i < size_; i++) {
			data_[i] = temp_buffer[i];
		}
		for (size_t i = size_; i < new_size; i++) {
			data_[i] = value_to_copy;
		}
		size_ = new_size;
	}
	else {
		if (new_size < size_) {
			for (size_t i = new_size; i < size_; i++) {
				delete &data_[i];
			}
			size_ = new_size;
		}
		else {
			for (size_t i = size_; i < new_size; i++) {
				data_[i] = value_to_copy;
			}
		}

	}
}


template<class T>
void Vector<T>::reserve(std::size_t new_capacity) {

	if (new_capacity <= capacity_) return;
	else {
		capacity_ = new_capacity;
		T temp_buffer[size_];
		std::copy(data_, data_ + size_, temp_buffer);
		delete[] data_;
		data_ = new T[capacity_];
		for (size_t i = 0; i < size_; i++)
		{
			data[i] = temp_buffer[i];
		}
	}
}


template<class T>
void Vector<T>::shrink_to_fit() {

	capacity_ = size_;
	T temp_buffer[size_];
	std::copy(data_, data_ + size_, temp_buffer);
	delete[] data_;
	data_ = new T[capacity_];
	for (size_t i = 0; i < size_; i++) {
		data_[i] = temp_buffer[i];
	}
}


template<class T>
void Vector<T>::assign(std::size_t count, const T& value_to_copy) {

	if (count <= capacity_) {
		clear();
		data_ = new T[capacity_];
		for (size_t i = 0; i < count; i++) {
			data_[i] = value_to_copy;
		}
		if (count > size_) size_ = count;
	}
	else {
		clear();
		size_ = count;
		capacity_ = size_ + CAPACITY_INCREMENT;
		data_ = new T[capacity_];
		for (std::size_t i = 0; i < size_; i++)
		{
			data_[i] = value_to_copy;
		}
		
	}
}


;
#endif // VECTOR_REALIZATION_H_