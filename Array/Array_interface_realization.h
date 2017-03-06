#ifndef ARRAY_INTERFACE_REALIZATION_H_
#define ARRAY_INTERFACE_REALIZATION_H_

template <class T>
const std::string  ArrayInterface<T>::OUT_OF_RANGE_EXC_TEXT = "Pos is more than size of the array!";

template <class T>
ArrayInterface<T>::ArrayInterface(std::size_t & size, T * data): 
	size_(size),
	data_(data){
}

template <class T>
T & ArrayInterface<T>::operator[](const std::size_t pos) const {
  return data_[pos];
}

template <class T>
T & ArrayInterface<T>::at(const std::size_t pos) const {
  if (pos >= size_) {
    throw std::out_of_range(OUT_OF_RANGE_EXC_TEXT);
  }
  return data_[pos];
}

template <class T>
T & ArrayInterface<T>::front() const {
  return *data_;
}

template <class T>
T & ArrayInterface<T>::back() const {
  if (size_ > 0) {
    return data_[size_ - 1];
  } else {
      return front();
  }
}

template <class T>
T * ArrayInterface<T>::data() const {
  return &front();
}

template <class T>
bool ArrayInterface<T>::empty() const {
  return size_ == 0;
}

template <class T>
std::size_t ArrayInterface<T>::size() const {
  return size_;
}

template <class T>
void ArrayInterface<T>::fill(const T & value) {
  for (std::size_t i = 0; i < size_; i++) {
    data_[i] = value;
  }
}

template <class T>
void ArrayInterface<T>::dump() const {
	for(std::size_t i=0; i<size_; ++i)
		std::cout << "[" << i << "] " << data_[i] << std::endl;
	std::cout << std::endl;
}

;
#endif