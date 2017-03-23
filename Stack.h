#pragma once

#include<string>
#include<cassert>
#include<iostream>
#include<fstream>
#include<exception>
#include<new>
#include"implementation/vector.hpp"

namespace ava
{

	//! Stack class is a custom realization of popular FILO data-structure Stack.
	template<class T>
	class Stack {
	public:
		//! Defualt constructor. Defualt capacity is 10
		Stack();

		//! Constructor that create stack with certain capacity
		Stack(size_t capacity);

		//! Copy constructor makes deep copy
		//! @param otherStack a stack which data are copied from
		Stack(const Stack& that);

		//! Destructor does nothing
		~Stack();

		//! Default stack capacity for default constructor
		static const size_t STACK_DEFAULT_CAPASITY = 10U;

		//! Function swaps to Stack objects
		//! @param first is the first Stack object
		//! @param second is the second Stack object
		void swap(Stack& that) {
			container_.swap(that.container_);
		}

		//! Assigning work is delegated to the containers of this object and other object
		//! @param other is another Stack object that is copied from
		const Stack& operator=(const Stack& that);

		//! Method for putting an element to the stack.
		//! @param elementToPush is an element which should be put in the stack.
		void push(T element_to_push);


		//! Method for taking an element off the stack.
		T pop();

		//! Method returns top element in the stack without poping.
		//! Use it when you want just check last element in the stack.
		T top() const;


		//! Method cheks whether the stack is empty.
		//! If it is empty then true is returned, otherwise false is returned.
		bool isEmpty() const;

		//! Method returns current size of the stack.
		size_t getSize() const;

		//! Method returns an object capacity.
		size_t getCapacity() const;

		//! It is a scilent verefier.
		//! It cheks whether the current object has normal state(if current size less than capacity).
		bool isStackOk() const;

		//! Method dumps current object to Stack_Dump.txt file which is saved in the current directory.
		void dump() const;

	private:
		Vector<T> container_;
	};
}// !namespace ava
