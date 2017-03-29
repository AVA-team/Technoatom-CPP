#ifndef _SHARED_PTR_IMPLEMENTATION_H_
#define _SHARED_PTR_IMPLEMENTATION_H_

namespace ava {
	template<class T>
	shared_ptr<T>::shared_ptr(T* p = nullptr) :
		proxy_ptr_(new typename shared_ptr<T>::Proxy(p)) {}

	template<class T>
	shared_ptr<T>::shared_ptr(const shared_ptr<T>& that) {
		proxy_ptr_ = that.proxy_ptr_;
		proxy_ptr_->increment_count();
	}

	template<class T>
	shared_ptr<T>::~shared_ptr() {
		proxy_ptr_->decrement_count();
		if (proxy_ptr_->get_count() == 0) {
			delete proxy_ptr_;
			delete this;
		}
	}

	template<class T>
	typename shared_ptr<T>::Proxy::Proxy(T* p = nullptr) {
		count_ = 1L;
		ptr_ = p;
	}

	template<class T>
	typename shared_ptr<T>::Proxy::~Proxy() {
		delete ptr_;
	}

	template<class T>
	T* typename shared_ptr<T>::Proxy::operator->() {
		return ptr_;
	}

	template<class T>
	void typename shared_ptr<T>::Proxy::increment_count() {
		++count_;
	}

	template<class T>
	void typename shared_ptr<T>::Proxy::decrement_count() {
		--count_;
	}

	template<class T>
	long int typename shared_ptr<T>::Proxy::get_count() const {
		return count_;
	}

	template<class T>
	T* typename shared_ptr<T>::Proxy::get_ptr() const {
		return ptr_;
	}

	template<class T>
	typename shared_ptr<T>::Proxy* shared_ptr<T>::operator->() const {
		return proxy_ptr_;
	}

	template<class T>
	T& shared_ptr<T>::operator*() {
		return *(proxy_ptr_->get_ptr());
	}

	template<class T>
	shared_ptr<T>::operator bool() const {
		return (proxy_ptr_->get_ptr() == nullptr);
	}

	template<class T>
	const shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& that) {
		proxy_ptr_->decrement_count();
		if (proxy_ptr_->get_count() == 0) {
			delete proxy_ptr_;
		}
		proxy_ptr_ = that.proxy_ptr_;
		proxy_ptr_->increment_count();
	}

	template<class T>
	void shared_ptr<T>::swap(shared_ptr<T>& that) {
		typename shared_ptr<T>::Proxy* temp_proxy_ptr = proxy_ptr_;
		proxy_ptr_ = that.proxy_ptr_;
		that.proxy_ptr_ = temp_proxy_ptr;
	}

	template<class  T>
	void shared_ptr<T>::reset(T* p = nullptr) {
		proxy_ptr_->decrement_count();
		if (proxy_ptr_->get_count() == 0) {
			delete proxy_ptr_;
		}
		proxy_ptr_ = new typename shared_ptr<T>::Proxy(p);
	}

	template<class T>
	T* shared_ptr<T>::get() const {
		return proxy_ptr_->get_ptr();
	}

	template<class T>
	long int shared_ptr<T>::use_count() const {
		return proxy_ptr_->get_count();
	}

	template<class T>
	bool shared_ptr<T>::unique() const {
		return (proxy_ptr_->get_count() == 1);
	}
}

#endif
