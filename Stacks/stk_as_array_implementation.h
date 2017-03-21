//!@file stk_as_mass_realization.h
//!\brief Реализация класса стека на основе массива в отдельном файле.
//! 
//!@author Корнилов Антон, 2017
//!@date 24.02.2017

#ifndef STK_AS_ARR_REALIZATION_H
#define STK_AS_ARR_REALIZATION_H

#include"container_interface.h"

    template <class T, template<class> ContainerType>
	Stack<T, ContainerType<T>>::Stack() : capacity_(0), num_items_(0), data_(nullptr) {}

	template <class T, template<class> ContainerType>
	Stack<T, ContainerType<T>>::Stack(size_t capacity) : capacity_(capacity), num_items_(0), data_(new T [capacity]) {}

	template <class T, template<class> ContainerType>
	void Stack<T, ContainerType<T>>::swap(Stack & other_stack){
		container_.swap(other_stack.container_);
	}

	template <class T, template<class> ContainerType>
	Stack<T, ContainerType<T>>::Stack(const Stack & other_stack) : container_(other_stack.container_){}

	template <class T, template<class> ContainerType>
	Stack<T, ContainerType<T>>::Stack(const ContainerType& container):container_(container){}

	template <class T, template<class> ContainerType>
	Stack<T, ContainerType<T>> & Stack<T, ContainerType<T>>::operator=(Stack other_stack){
		swap(other_stack);
		return *this;
	}

	template <class T, template<class> ContainerType>
	Stack<T, ContainerType<T>>::~Stack(){
		//delete [] data_;
	}

	template <class T, template<class> ContainerType>
	void Stack<T, ContainerType<T>>::dump() const{
		const unsigned num_dashes = 50, num_chars1 = 11, num_chars2 = 7, num_chars3 = 21;
		std::cout << std::setfill('-') << std::setw(num_dashes) << "" << std::setfill(' ') << std::endl;
		std::cout << "   Stack:\n\tnum. of items:" << std::setw(num_chars1) << container_.size();
		
		std::cout << "Elements:" << std::endl;
		std::size_t i = 0;
		for(auto it = container_.begin(); it != container_.end(); ++it, ++i){
			std::cout << "\t[" << i << "] " << " = " << std::dec << *it << std::endl;
		}
		std::cout << std::setfill('-') << std::setw(num_dashes) << "" << std::setfill(' ') << std::endl;
	}

	template <class T, template<class> ContainerType>
	bool Stack<T, ContainerType<T>>::empty() const{
		return container_.size() == 0;
	}

	template <class T, template<class> ContainerType>
	size_t Stack<T, ContainerType<T>>::size() const{
		return container_.size();
	}

	template <class T, template<class> ContainerType>
	void Stack<T, ContainerType<T>>::push(const T& element){
		/*if (num_items_ == capacity_){
			const unsigned capacity_multiplier = 2;
			if (capacity_ == 0){
				++capacity_;
			}
			else{
				capacity_ *= capacity_multiplier;
			}
			T * new_data = new T [capacity_];
			for(size_t i=0; i<num_items_; ++i){
				new_data[i] = data_[i];
			}
			delete [] data_;
			data_ = new_data;
		}
		data_[num_items_++] = element;*/
		container_.push_back();
	}

	template <class T, template<class> ContainerType>
	void Stack<T, ContainerType<T>>::pop(){
		ASSERT_NOT_EMPTY();
		container_.pop_back();
	}

	template <class T, template<class> ContainerType>
	T& Stack<T, ContainerType<T>>::top(){
		ASSERT_NOT_EMPTY();
		return container_.at(container_.size()-1);
	}

;
#endif //STK_AS_ARR_REALIZATION_H