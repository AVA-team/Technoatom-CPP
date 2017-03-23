#pragma once

#include"Stack.h"

namespace ava {

	template<class T>
	Stack<T>::Stack() : container_(Vector<T>(Stack<T>::STACK_DEFAULT_CAPASITY)) {}


	template<class T>
	Stack<T>::Stack(size_t capacity) : container_(Vector<T>(capacity)) {}


	template<class T>
	Stack<T>::Stack(const Stack& that) : container_(Vector<T>(that.container_)) {}


	template<class T>
	const Stack<T>& Stack<T>::operator=(const Stack& that) {
		Stack<T> victim(that);
		swap(victim);
		return (*this);
	}


	template<class T>
	Stack<T>::~Stack()
	{}


	template<class T>
	void Stack<T>::push(T element_to_push) {
		container_.push_back(element_to_push);
	}


	template<class T>
	T Stack<T>::pop() {
		try {
			T toReturn = container_[container_.size() - 1];
			container_.pop_back();
			return toReturn;
		}
		catch (const std::length_error&) {
			throw std::length_error("Failed attempt to pop empty stack in Stack::pop()\n");
		}
	}


	template<class T>
	T Stack<T>::top() const {
		if (container_.empty()) {
			throw std::length_error("Failed attempt to call top() from empty stack in Stack::top()\n");
		}
		else {
			return container_.back();
		}
	}


	template <class T>
	bool Stack<T>::isEmpty() const {
		return container_.empty();
	}


	template <class T>
	std::size_t Stack<T>::getSize() const {
		return container_.size();
	}


	template <class T>
	std::size_t Stack<T>::getCapacity() const {
		return container_.capacity();
	}


	template <class T>
	bool Stack<T>::isStackOk() const {
		return container_.size() <= container_.capacity();
	}


	template <class T>
	void Stack<T>::dump() const {
		std::string dumpContent = (isStackOk()) ? "Stack (OK)\n\t{\n" : "Stack (ERROR)\n\t{\n";
		dumpContent += "\tCapacity = " + std::to_string(container_.capacity()) + "\n" + "\tSize = " + std::to_string(container_.size()) + "\n\n\t\tdata[" + std::to_string(container_.capacity()) + "]:\n\t\t{\n";
		for (std::size_t i = 0; i < container_.capacity(); i++) {
			if (i < container_.size()) {
				dumpContent += "   \t*\tElement ¹ " + std::to_string(i) + ")\t" + std::to_string(container_[i]) + "\n";
			}
			else {
				dumpContent += "\t\tElement ¹ " + std::to_string(i) + ")\t" + std::to_string(container_[i]) + " (TRASH)\n";
			}
		}
		dumpContent += "\t\t}\n\t}\n";
		ofstream fout;
		fout.open("Stack_Dump.txt");//open file Stack_Dump.txt if it exist or create new file
		fout << __DATE__ << std::endl << __TIME__ << "\n\n\n" << dumpContent;
		fout.close();
		std::cout << "Stack dump file was saved in current directory. See Stack_Dump.txt\n";
	}

}//! namespace ava