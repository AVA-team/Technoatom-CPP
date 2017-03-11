#ifndef ARRAY_INTERFACE_REALIZATION_H_
#define ARRAY_INTERFACE_REALIZATION_H_

#define size_ container_.size_
#define data_ container_.data_

template <class T, class ContainerType>
const std::string  ArrayInterface<T, ContainerType>::OUT_OF_RANGE_EXC_TEXT = "Pos is out of range of array size!";

template <class T, class ContainerType>
ArrayInterface<T, ContainerType>::ArrayInterface(ContainerType & container): 
	container_(container) {
}

template <class T, class ContainerType>
const T & ArrayInterface<T, ContainerType>::operator[](const std::size_t pos) const {
  return data_[pos];
}

template <class T, class ContainerType>
T & ArrayInterface<T, ContainerType>::at(const std::size_t pos) const {
  if (pos >= size_) {
    throw std::out_of_range(OUT_OF_RANGE_EXC_TEXT);
  }
  return data_[pos];
}

template <class T, class ContainerType>
T & ArrayInterface<T, ContainerType>::front() const {
  return *data_;
}

template <class T, class ContainerType>
T & ArrayInterface<T, ContainerType>::back() const {
  if (size_ > 0) {
    return data_[size_ - 1];
  } else {
      return front();
  }
}

template <class T, class ContainerType>
T * ArrayInterface<T, ContainerType>::data() const {
  return &front();
}

template <class T, class ContainerType>
bool ArrayInterface<T, ContainerType>::empty() const {
  return size_ == 0;
}

template <class T, class ContainerType>
std::size_t ArrayInterface<T, ContainerType>::size() const {
  return size_;
}

template <class T, class ContainerType>
void ArrayInterface<T, ContainerType>::fill(const T & value) {
  for (std::size_t i = 0; i < size_; i++) {
    data_[i] = value;
  }
}

template <class T, class ContainerType>
void ArrayInterface<T, ContainerType>::dump() const {
	for(std::size_t i=0; i<size_; ++i)
		std::cout << "[" << i << "] " << data_[i] << std::endl;
	std::cout << std::endl;
}

#undef size_
#undef data_
;
#endif