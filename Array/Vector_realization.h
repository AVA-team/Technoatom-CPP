#ifndef VECTOR_REALIZATION_H_
#define VECTOR_REALIZATION_H_


template <class T>
Vector<T>::Vector(std::size_t size = 2):
  size_(size),
  data_(new T[size]),
  ArrayInterface(size_, data_) {
	  ArrayInterface::data_ = data_;
}

template <class T>
Vector<T>::~Vector() {
  delete[] data_;
  data_ = nullptr;
}

template <class T>
const Vector<T> & Vector<T>::operator=(const Vector & that){
	if(this == &that) {
		return *this;
	}
	Vector<T> tmp_vector(that);
	swap(tmp_vector);
	return *this;
}

template <class T>
Vector<T>::Vector(const Vector & that):
  size_(that.size_),
  data_(new T[that.size_]),
  ArrayInterface(size_, nullptr) {
	  ArrayInterface::data_ = data_;
	  for (std::size_t i = 0; i < size_; i++) {
		data_[i] = that[i];
	  }
}


template <class T>
void Vector<T>::swap(Vector & that) {
	std::swap(size_, that.size_);
	std::swap(data_, that.data_);
	std::swap(ArrayInterface::data_, that.ArrayInterface::data_);
}

;
#endif // VECTOR_REALIZATION_H_