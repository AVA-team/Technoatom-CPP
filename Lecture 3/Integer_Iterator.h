#pragma once
template<class T>
class Array_Iterator
{
public:
	Array_Iterator(T* val_p);
	~Array_Iterator();
	T& operator*();
	Array_Iterator& operator++();
	Array_Iterator& operator--();
	Array_Iterator operator++(int);//postfix
	Array_Iterator operator--(int);//postfix
	bool operator==(const Array_Iterator<T>& other);
	bool operator!=(const Array_Iterator<T>& other);


private:
	T* val_p_;
};

template<class T>
Array_Iterator<T>::Array_Iterator(T* val_p)
{
	val_p_ = val_p;
}

template<class T>
Array_Iterator<T>::~Array_Iterator()
{
}

template<class T>
T& Array_Iterator<T>::operator*()
{
	return *val_p_;
}

template<class T>
Array_Iterator<T>& Array_Iterator<T>::operator++()
{
	++val_p_;
	return *this;
}

template<class T>
Array_Iterator<T>& Array_Iterator<T>::operator--()
{
	--val_p_;
	return *this;
}

template<class T>
Array_Iterator<T> Array_Iterator<T>::operator++(int)
{
	return Array_Iterator<T>(++val_p_);
}

template<class T>
Array_Iterator<T> Array_Iterator<T>::operator--(int)
{
	return Array_Iterator<T>(--val_p_);
}

template<class T>
bool Array_Iterator<T>::operator==(const Array_Iterator<T>& other)
{
	return *val_p_ == *(other.val_p_);
}

template<class T>
bool Array_Iterator<T>::operator!=(const Array_Iterator<T>& other)
{
	return !(*val_p_ == *(other.val_p_));
}