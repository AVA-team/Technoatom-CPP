#ifndef AUTO_PTR_IMPLEMENTATION_H_
#define AUTO_PTR_IMPLEMENTATION_H_

namespace ava {
	template<class T>
	inline auto_ptr<T>::auto_ptr(T * p = nullptr) :
		ptr_(p) { }

	template<class T>
	auto_ptr<T>::auto_ptr(auto_ptr & that) :
		ptr_(that.release()) { }

	template<class T>
	auto_ptr<T>::~auto_ptr()
	{
		delete ptr_;
	}

	template<class T>
	T * auto_ptr<T>::get() const
	{
		return ptr_;
	}

	template<class T>
	T & auto_ptr<T>::operator*() const
	{
		return *ptr_;
	}

	template<class T>
	T * auto_ptr<T>::operator->() const
	{
		return ptr_;
	}

	template<class T>
	auto_ptr<T> & auto_ptr<T>::operator=(auto_ptr & that)
	{
		if (this != &that) {
			delete ptr_;
			ptr_ = that.release();
		}
		return *this;
	}

	template<class T>
	T * auto_ptr<T>::release()
	{
		T * tmp_ptr = ptr_;
		ptr_ = nullptr;
		return tmp_ptr;
	}

	template<class T>
	void auto_ptr<T>::reset(T * p = nullptr)
	{
		delete ptr_;
		ptr_ = p;
	}
}

#endif //AUTO_PTR_IMPLEMENTATION_H_