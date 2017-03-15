#ifndef ARRAY_INTERFACE_REALIZATION_H_
#define ARRAY_INTERFACE_REALIZATION_H_

template <class T>
const std::string  ContainerInterface<T>::OUT_OF_RANGE_EXC_TEXT = "Pos is out of range of array size!";

template <class T>
ContainerInterface<T>::ContainerInterface(T* data, std::size_t size): 
	data_(data),
	size_(size) {
}

template <class T>
const T & ContainerInterface<T>::operator[](const std::size_t pos) const {
  return data_[pos];
}

template <class T>
T & ContainerInterface<T>::at(const std::size_t pos) const {
  if (pos >= size_) {
    throw std::out_of_range(OUT_OF_RANGE_EXC_TEXT);
  }
  return data_[pos];
}

template <class T>
T & ContainerInterface<T>::front() const {
  return *data_;
}

template <class T>
T & ContainerInterface<T>::back() const {
  if (size_ > 0) {
    return data_[size_ - 1];
  } else {
      return front();
  }
}

template <class T>
T * ContainerInterface<T>::data() const {
  return &front();
}

template <class T>
bool ContainerInterface<T>::empty() const {
  return size_ == 0;
}

template <class T>
std::size_t ContainerInterface<T>::size() const {
  return size_;
}

template <class T>
void ContainerInterface<T>::fill(const T & value) {
  for (std::size_t i = 0; i < size_; i++) {
    data_[i] = value;
  }
}

template <class T>
void ContainerInterface<T>::dump() const {
	for(std::size_t i=0; i<size_; ++i)
		std::cout << "[" << i << "] " << data_[i] << std::endl;
	std::cout << std::endl;
}

template <class T>
typename ContainerInterface<T>::Array_Iterator ContainerInterface<T>::begin() {
	return Array_Iterator(data_);
}

template <class T>
typename ContainerInterface<T>::Array_Iterator ContainerInterface<T>::end() {
	return Array_Iterator(data_ + size_);
}

template <class T>
ContainerInterface<T>::Array_Iterator::Array_Iterator(T* val_p) {
	val_p_ = val_p;
}

template <class T>
ContainerInterface<T>::Array_Iterator::~Array_Iterator() {}

template <class T>
T& ContainerInterface<T>::Array_Iterator::operator*() {
	return *val_p_;
}

template <class T>
T* ContainerInterface<T>::Array_Iterator::operator->() {
	return val_p_;
}

template <class T>
typename ContainerInterface<T>::Array_Iterator& ContainerInterface<T>::Array_Iterator::operator++() {
	++val_p_;
	return *this;
}

template <class T>
typename ContainerInterface<T>::Array_Iterator& ContainerInterface<T>::Array_Iterator::operator--() {
	--val_p_;
	return *this;
}

template <class T>
typename ContainerInterface<T>::Array_Iterator ContainerInterface<T>::Array_Iterator::operator++(int) {
	return ContainerInterface<T>::Array_Iterator(++val_p_);
}


template <class T>
typename ContainerInterface<T>::Array_Iterator ContainerInterface<T>::Array_Iterator::operator--(int) {
	return ContainerInterface<T>::Array_Iterator(--val_p_);
}

template <class T>
bool ContainerInterface<T>::Array_Iterator::operator==(const typename ContainerInterface<T>::Array_Iterator& other) {
	return *val_p_ == *(other.val_p_);
}

template <class T>
bool ContainerInterface<T>::Array_Iterator::operator!=(const typename ContainerInterface<T>::Array_Iterator& other) {
	return !(*val_p_ == *(other.val_p_));
}

;
#endif