#pragma once

#include<memory>
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
		else if(pos >= capacity_) {
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
		if (pos >= size_) {
			throw std::out_of_range("Failed attempt to invoke method 'Vector<T>::insert()':Index (pos) bigger than current size\n");
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
		capacity_ = new_capacity;
		auto new_data = new T[capacity_];
		std::copy(begin(), end(), new_data);
		delete[] data_;
		data_ = new_data;
	}


	template<class T>
	void Vector<T>::shrink_to_fit() {
		capacity_ = size_;
		auto temp_buf = new T[capacity_];
		std::copy(begin(), end(), temp_buf);
		delete[] data_;
		data_ = temp_buf;
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

	void* Vector<bool>::operator new(std::size_t size, std::size_t n, int init_val) {
		void* p = malloc(size * n);
		memset(p, init_val, size * n);
		return p;
	}

	Vector<bool>::Vector() :
		bits_capacity_(DEFAULT_BITS_CAPACITY_),
		bits_size_(0),
		elements_capacity_(DEFAULT_ELEMENT_CAPACITY_),
		elements_size_(0),
		data_(nullptr) {
		data_ = new uint[DEFAULT_ELEMENT_CAPACITY_];
		for (std::size_t i = 0; i < elements_capacity_; i++) {
			data_[i] = 0;
		}
	}

	std::size_t Vector<bool>::get_elements_count_from_bits_count(std::size_t bits_count) {
		return bits_count / BITS_PER_ELEMENT_ + 1;
	}

	Vector<bool>::Vector(std::size_t capacity) :
		bits_capacity_(capacity),
		bits_size_(0),
		elements_capacity_(get_elements_count_from_bits_count(capacity)),
		elements_size_(0),
		data_(nullptr) {
		data_ = new uint[get_elements_count_from_bits_count(capacity)];
		for (std::size_t i = 0; i < elements_capacity_; i++) {
			data_[i] = 0;
		}
	}

	Vector<bool>::Vector(const Vector<bool>& that) :
		bits_capacity_(that.bits_capacity_),
		bits_size_(that.bits_size_),
		elements_capacity_(that.elements_capacity_),
		elements_size_(that.elements_size_),
		data_(nullptr) {
		data_ = new uint[that.elements_capacity_];
		std::copy(that.data_, that.data_ + that.elements_size_, data_);
	}

	Vector<bool>::Vector(const std::initializer_list<bool>& init_list) {
		auto bits_size = init_list.size();
		auto elements_size = get_elements_count_from_bits_count(bits_size);
		elements_capacity_ = (DEFAULT_ELEMENT_CAPACITY_ >= elements_size) ? DEFAULT_ELEMENT_CAPACITY_ : elements_size;
		bits_capacity_ = elements_capacity_ * BITS_PER_ELEMENT_;
		bits_size_ = bits_size;
		elements_size_ = elements_size;
		data_ = new uint[elements_capacity_];
		for (std::size_t i = 0; i < elements_capacity_; i++) {
			data_[i] = 0;
		}
		int i = 0;
		for (auto it = init_list.begin(); it != init_list.end(); ++it, ++i) {
			int element_pos = i / BITS_PER_ELEMENT_;
			int bit_pos = i % BITS_PER_ELEMENT_;
			if (*it) {
				data_[element_pos] |= (1U << bit_pos);
			}
			else {
				data_[element_pos] &= ~(1U << bit_pos);
			}
		}
	}


	Vector<bool>::Vector(Vector<bool>&& that) :
		bits_capacity_(0),
		bits_size_(0),
		elements_capacity_(0),
		elements_size_(0),
		data_(nullptr) {
		swap(that);
	}


	Vector<bool>::Vector(const std::size_t size, bool val) {
		bits_size_ = size;
		elements_size_ = get_elements_count_from_bits_count(size);
		elements_capacity_ = (DEFAULT_ELEMENT_CAPACITY_ >= elements_size_) ? DEFAULT_ELEMENT_CAPACITY_ : elements_size_;
		bits_capacity_ = elements_capacity_ * BITS_PER_ELEMENT_;
		data_ = new uint[elements_capacity_];
		for (std::size_t i = 0; i < elements_capacity_; i++) {
			data_[i] = 0;
		}
		if (val) {
			for (std::size_t i = 0; i < bits_size_; i++) {
				int element_pos = i / BITS_PER_ELEMENT_;
				int bit_pos = i % BITS_PER_ELEMENT_;
				data_[element_pos] |= (1U << bit_pos);
			}
		}
		else {
			for (std::size_t i = 0; i < bits_size_; i++) {
				int element_pos = i / BITS_PER_ELEMENT_;
				int bit_pos = i % BITS_PER_ELEMENT_;
				data_[element_pos] &= ~(1U << bit_pos);
			}
		}
	}


	void Vector<bool>::clear() {
		bits_capacity_ = 0;
		bits_size_ = 0;
		elements_capacity_ = 0;
		elements_size_ = 0;
		delete[] data_;
		data_ = nullptr;
	}


	Vector<bool>::~Vector() {
		clear();
	}


	Vector<bool>::BitIterator::BitIterator(std::size_t element_pos, std::size_t bit_pos, uint* data):
		element_pos_(element_pos),
		bit_pos_(bit_pos),
		data_(data){}


	Vector<bool>::BitIterator::~BitIterator(){}


	Vector<bool>::BitReference Vector<bool>::BitIterator::operator*() {
		return BitReference(element_pos_, bit_pos_, data_);
	}

	Vector<bool>::BitIterator Vector<bool>::BitIterator::operator++() {
		if (bit_pos_ + 1 == BITS_PER_ELEMENT_) {
			++element_pos_;
			bit_pos_ = 0;
		}
		else {
			++bit_pos_;
		}
		return *this;
	}


	Vector<bool>::BitIterator Vector<bool>::BitIterator::operator--() {
		if (bit_pos_ == 0) {
			--element_pos_;
			bit_pos_ = BITS_PER_ELEMENT_ - 1;
		}
		else {
			--bit_pos_;
		}
		return *this;
	}


	//postfix
	Vector<bool>::BitIterator Vector<bool>::BitIterator::operator++(int) {
		BitIterator to_return(*this);
		++(*this);
		return to_return;
	}


	//postfix
	Vector<bool>::BitIterator Vector<bool>::BitIterator::operator--(int) {
		BitIterator to_return(*this);
		--(*this);
		return to_return;
	}


	bool Vector<bool>::BitIterator::operator==(const Vector<bool>::BitIterator& that) {
		return (element_pos_ == that.element_pos_) && (bit_pos_ == that.bit_pos_) && (data_ == that.data_);
	}


	bool Vector<bool>::BitIterator::operator!=(const Vector<bool>::BitIterator& that) {
		return !(*this == that);
	}


	Vector<bool>::BitReference::BitReference(std::size_t element_pos, std::size_t bit_pos, uint* data):
		element_pos_(element_pos),
		bit_pos_(bit_pos),
		data_(data){}


	Vector<bool>::BitReference::~BitReference(){}


	bool Vector<bool>::BitReference::get_value() const {
		int bit = data_[element_pos_] & (1U << bit_pos_);
		return !!bit;
	}


	void Vector<bool>::BitReference::set_value(bool val) {
		if (val) {
			data_[element_pos_] |= (1U << bit_pos_);
		}
		else {
			data_[element_pos_] &= ~(1U << bit_pos_);
		}
	}

	const Vector<bool>::BitReference& Vector<bool>::BitReference::operator=(const Vector<bool>::BitReference& that) {
		element_pos_ = that.element_pos_;
		bit_pos_ = that.bit_pos_;
		data_ = that.data_;
		set_value(that.get_value());
		return *this;
	}


	const Vector<bool>::BitReference& Vector<bool>::BitReference::operator=(bool val) {
		set_value(val);
		return *this;
	}


	bool Vector<bool>::BitReference::operator==(bool that) {
		bool curr_val = get_value();
		return curr_val == that;
	}


	Vector<bool>::BitReference::operator bool() {
		return get_value();
	}


	const Vector<bool>& Vector<bool>::operator=(const Vector<bool>& that) {
		Vector<bool> victim(that);
		swap(victim);
		return *this;
	}

	Vector<bool>& Vector<bool>::operator=(Vector<bool>&& that) {
		swap(that);
		return *this;
	}

	Vector<bool>::BitReference Vector<bool>::operator[](const std::size_t pos) {
		if (pos >= bits_capacity_) {
			reserve(pos + 1);
		}
		if (pos >= bits_size_) {
			bits_size_ = pos + 1;
			elements_size_ = get_elements_count_from_bits_count(bits_size_);
		}
		auto element_pos = pos / BITS_PER_ELEMENT_, bit_pos = pos % BITS_PER_ELEMENT_;
		return BitReference(element_pos, bit_pos, data_);
	}


	bool Vector<bool>::operator[](const std::size_t pos) const {
		if (pos >= bits_size_) {
			throw std::length_error("Failed attempt to invocke 'bool Vector<bool>::operator[const std::size_t pos]': position is begger or than current size\n");
		}
		auto element_pos = pos / BITS_PER_ELEMENT_, bit_pos = pos % BITS_PER_ELEMENT_;
		return BitReference(element_pos, bit_pos, data_);
	}


	void Vector<bool>::swap(Vector<bool>& that) {
		std::swap(bits_capacity_, that.bits_capacity_);
		std::swap(bits_size_, that.bits_size_);
		std::swap(elements_capacity_, that.elements_capacity_);
		std::swap(elements_size_, that.elements_size_);
		std::swap(data_, that.data_);
	}

	void Vector<bool>::push_back(bool val) {
		auto new_bits_size = bits_size_ + 1;
		if (new_bits_size > bits_capacity_) {
			reserve(bits_capacity_ * CAPACITY_MULTIPLY_KOEFF);
		}
		auto element_pos = bits_size_ / BITS_PER_ELEMENT_,
			bit_pos = bits_size_ % BITS_PER_ELEMENT_;
		if (val) {
			data_[element_pos] |= (1U << bit_pos);
		}
		else {
			data_[element_pos] &= ~(1U << bit_pos);
		}
		bits_size_ = new_bits_size;
		elements_size_ = get_elements_count_from_bits_count(new_bits_size);
	}

	void Vector<bool>::pop_back() {
		if (bits_size_ == 0) {
			throw std::length_error("Failed attempt to invoke 'Vector<bool>::pop_back()': current size equals 0\n");
		}
		--bits_size_;
	}


	void Vector<bool>::insert(std::size_t bit_pos, std::size_t bits_count, bool val) {
		if (bit_pos >= bits_size_) {
			throw std::out_of_range("Failed attempt to invoke method 'Vector<T>::insert()':Index (pos) bigger than current size\n");
		}
		auto new_bits_size = bits_size_ + bits_count,
			new_elements_size = get_elements_count_from_bits_count(new_bits_size);
		//буфер для хранения старых данных
		std::unique_ptr<uint> temp_buff(new uint[new_elements_size]);
		std::copy(data_, data_ + elements_size_, temp_buff.get());
		if (new_bits_size > bits_capacity_) {
			reserve(new_bits_size);
		}
		for (std::size_t i = 0; i < bit_pos; i++) {
			auto curr_element_pos = i / BITS_PER_ELEMENT_,
				curr_bit_pos = i % BITS_PER_ELEMENT_;
			BitReference curr_bit(curr_element_pos, curr_bit_pos, temp_buff.get());
			if (curr_bit) {
				data_[curr_element_pos] |= (1U << curr_bit_pos);
			}
			else {
				data_[curr_element_pos] &= ~(1U << curr_bit_pos);
			}
		}
		auto bits_end_pos = bit_pos + bits_count;
		for (std::size_t i = bit_pos; i < bits_end_pos; i++) {
			auto curr_element_pos = i / BITS_PER_ELEMENT_,
				curr_bit_pos = i % BITS_PER_ELEMENT_;
			if(val) {
				data_[curr_element_pos] |= (1U << curr_bit_pos);
			}
			else {
				data_[curr_element_pos] &= ~(1U << curr_bit_pos);
			}
		}
		for (std::size_t i = bits_end_pos; i < new_bits_size; i++) {
			auto curr_element_pos = i / BITS_PER_ELEMENT_,
				curr_bit_pos = i % BITS_PER_ELEMENT_,
				curr_element_pos_in_buff = (i - bits_count) / BITS_PER_ELEMENT_,
				curr_bit_pos_in_buff = (i - bits_count) % BITS_PER_ELEMENT_;
			BitReference curr_bit(curr_element_pos_in_buff, curr_bit_pos_in_buff, temp_buff.get());
			if (curr_bit) {
				data_[curr_element_pos] |= (1U << curr_bit_pos);
			}
			else {
				data_[curr_element_pos] &= ~(1U << curr_bit_pos);
			}
		}
		bits_size_ = new_bits_size;
	}


	std::size_t Vector<bool>::get_proper_new_element_capacity(std::size_t new_bits_size) {
		if (new_bits_size <= bits_capacity_) {
			return elements_capacity_;
		}
		auto new_elements_capacity = get_elements_count_from_bits_count(new_bits_size);
		return new_elements_capacity;
	}


	void Vector<bool>::resize(std::size_t new_bits_size, bool val = false) {
		auto new_elements_size = get_elements_count_from_bits_count(new_bits_size);
		if (new_bits_size > bits_capacity_) {
			reserve(new_bits_size);
		}
		else if (new_bits_size > bits_size_) {
			for (std::size_t i = bits_size_; i < new_bits_size; i++) {
				auto element_pos = i / BITS_PER_ELEMENT_,
					bit_pos = i % BITS_PER_ELEMENT_;
				if (val) {
					data_[element_pos] |= (1U << bit_pos);
				}
				else {
					data_[element_pos] &= ~(1U << bit_pos);
				}
			}
		}
		bits_size_ = new_bits_size;
		elements_size_ = new_elements_size;
	}

	void Vector<bool>::reserve(std::size_t new_bits_capacity) {
		if (new_bits_capacity <= bits_capacity_) {
			return;
		}
		auto new_element_capacity = get_elements_count_from_bits_count(new_bits_capacity);
		std::unique_ptr<uint> temp_buff(new uint[elements_size_]);
		std::copy(data_, data_ + elements_size_, temp_buff.get());
		delete[]data_;
		data_ = new uint[new_element_capacity];
		std::copy(temp_buff.get(), temp_buff.get() + elements_size_, data_);
		bits_capacity_ = new_bits_capacity;
		elements_capacity_ = new_element_capacity;
	}

	void Vector<bool>::shrink_to_fit() {
		bits_capacity_ = bits_size_;
		elements_capacity_ = elements_size_;
		auto temp_buff = new uint[elements_capacity_];
		std::copy(data_, data_ + elements_size_, temp_buff);
		data_ = temp_buff;
	}

	void Vector<bool>::assign(std::size_t count, bool val) {
		bits_size_ = count;
		elements_size_ = get_elements_count_from_bits_count(bits_size_);
		if (count > bits_capacity_) {
			auto new_elements_capacity = get_proper_new_element_capacity(count);
			delete[]data_;
			data_ = new uint[new_elements_capacity];
			bits_capacity_ = new_elements_capacity * BITS_PER_ELEMENT_;
			elements_capacity_ = new_elements_capacity;
		}
		for (std::size_t i = 0; i < bits_size_; i++) {
			auto curr_element_pos = i / BITS_PER_ELEMENT_,
				curr_bit_pos = i % BITS_PER_ELEMENT_;
			if (val) {
				data_[curr_element_pos] |= (1U << curr_bit_pos);
			}
			else {
				data_[curr_element_pos] &= ~(1U << curr_bit_pos);
			}
		}
	}

	bool Vector<bool>::at(std::size_t pos) const {
		if (pos >= bits_size_) {
			throw std::length_error("Failed attempt to invoke 'bool Vector<bool>::at(std::size_t pos)': pos is equals current size or bigger one\n");
		}
		auto element_pos = pos / BITS_PER_ELEMENT_,
			bit_pos = pos % BITS_PER_ELEMENT_;
		return BitReference(element_pos, bit_pos, data_);
	}

	bool Vector<bool>::front() const {
		if (bits_size_ == 0) {
			throw std::length_error("Failed attempt to invoke 'bool Vector<bool>::front()':vector is empty\n");
		}
		std::size_t element_pos = 0, bit_pos = 0;
		return BitReference(element_pos, bit_pos, data_);
	}

	bool Vector<bool>::back() const {
		if (bits_size_ == 0) {
			throw std::length_error("Failed attempt to invoke 'bool Vector<bool>::front()':vector is empty\n");
		}
		return BitReference(elements_size_ - 1, bits_size_ - 1, data_);
	}

	bool Vector<bool>::empty() const {
		return bits_size_ == 0;
	}

	Vector<bool>::BitIterator Vector<bool>::begin() const {
		return BitIterator(0, 0, data_);
	}

	Vector<bool>::BitIterator Vector<bool>::end() const {
		return BitIterator(elements_size_, bits_size_, data_);
	}

}