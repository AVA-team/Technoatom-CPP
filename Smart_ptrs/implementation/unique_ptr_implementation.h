#ifndef _UNIQUE_PTR_IMPLEMENTATION_H_
#define _UNIQUE_PTR_IMPLEMENTATION_H_

namespace ava {
	template<class T>
	unique_ptr<T>::unique_ptr(T* p) : 
		ptr_(p){}

	template<class T>
	unique_ptr<T>::unique_ptr(unique_ptr<T>&& that) :
		ptr_(nullptr) {
		ptr_ = that.release();
	}

	template<class T>
	unique_ptr<T>::~unique_ptr() {
		delete ptr_;
	}

	template<class T>
	unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>&& that) {
		if (this != &that) {
			delete ptr_;
			ptr_ = that.release();
		}
		return *this;
	}

	template<class T>
	T& unique_ptr<T>::operator*() {
		return *ptr_;
	}

	template<class T>
	T* unique_ptr<T>::operator->() {
		return ptr_;
	}

	template<class T>
	T* unique_ptr<T>::get() const {
		return ptr_;
	}

	template<class T>
	unique_ptr<T>::operator bool() const {
		return ptr_ != nullptr;
	}

	template<class T>
	T* unique_ptr<T>::release() {
		T* temp_ptr = ptr_;
		ptr_ = nullptr;
		return temp_ptr;
	}

	template<class T>
	void unique_ptr<T>::reset(T* p = nullptr) {
		delete ptr_;
		ptr_ = p;
	}

	template<class T>
	void unique_ptr<T>::swap(unique_ptr<T>& that) {
		T* temp_ptr = ptr_;
		ptr_ = that.ptr_;
		that.ptr_ = temp_ptr;
	}
}

#endif // _UNIQUE_PTR_IMPLEMENTATION_H_
