#include<exception>


namespace AVA
{

	typedef double Stack_Content_Type;

	/**
	Stack class is a custom realization of popular FILO data-structure Stack.
	Author - Anam Akhmed. ahmedanam@mail.ru
	*/
	class Stack
	{
	public:
		/**
		Defualt constructor. Defualt capacity is 10
		*/
		Stack();

		/**
		Constructor that create stack with certain capacity
		*/
		Stack(size_t capacity);

		/**
		Copy constructor makes deep copy
		@param otherStack a stack which data are copied from
		*/
		Stack(const Stack& otherStack);

		/**
		Destructor deletes dynamic allocated memory for holding stack data.
		Also it set current stack size to (capacity + 1) to break current object to avoid using it after its destroying.
		*/
		~Stack();

		/**
		Default stack capacity for default cobstructor
		*/
		static const size_t STACK_DEFAULT_CAPASITY = 10U;

		friend void swap(Stack& first, Stack& second)
		{
			using std::swap;

			swap(first.capacity_, second.capacity_);
			swap(first.size_, second.size_);
			swap(first.data_, second.data_);
		}

		/**
		Overriding the assignment operation for this class making deep copy
		*/
		const Stack& operator=(const Stack& other);

		/**
		Method for putting an element to the stack.
		@param elementToPush is an element which should be put in the stack.
		If stack can't hold more elements false is returned, otherwise true is returned.
		*/
		bool push(Stack_Content_Type elementToPush);


		/**
		Method for taking an element off the stack.
		*/
		Stack_Content_Type pop();

		/**
		Method returns top element in the stack without poping.
		Use it when you want just check last element in the stack.
		*/
		Stack_Content_Type top() const;


		/**
		Method cheks whether the stack is empty.
		If it is empty then true is returned, otherwise false is returned.
		*/
		bool isEmpty() const;

		/**
		Method returns current size of the stack.
		*/
		size_t getSize() const;

		/**
		Method returns an object capacity.
		*/
		size_t getCapacity() const;

		/**
		It is a scilent verefier.
		It cheks whether the current object has normal state (if current size less than capacity).
		*/
		bool isStackOk() const;

		/**
		Method dumps current object to Stack_Dump.txt file which is saved in the current directory.
		*/
		void dump() const;

		/**
		Class indicates that stack is empty.
		*/
		class EmptyStackException : public std::exception
		{
		public:
			EmptyStackException(const char* const message) : exception(message) { }

			~EmptyStackException() { }
		};

	private:

		void deepCopy(const Stack& other);

		Stack_Content_Type* data_;
		size_t size_, capacity_;

	};

}
