#pragma once

#include <string>
#include <stdexcept>
#include <initializer_list>
#include <string>
#include <ostream>
#include <iostream>

// Объявление Array
template <typename T> class Array;

template <typename S> bool operator== (const Array<S>&, const Array<S>&);
template <typename S> bool operator!= (const Array<S>&, const Array<S>&);
template <typename S> std::ostream& operator<<(std::ostream& os, const Array<S>& array);

template <typename T>
class Array
{

public: // создание, удаление
	Array();
	explicit Array(size_t size);
	Array(std::initializer_list<T> l);
	Array(const Array& other);
	Array& operator=(const Array& other);
	virtual ~Array();
public: // доступ к элементам
	T& operator[] (size_t index);
	const T& operator[] (size_t index) const;
	size_t GetSize() const noexcept;
	const T& GetFront() const;
	const T& GetBack() const;
	bool Find(int value, size_t& index) const noexcept;
public: // изменение 
	void Resize(size_t size);
	void PushFront(const T& value);
	void PopFront();
	void PushBack(const T& value);
	void PopBack();
	void Insert(const T& value, size_t index);
	void Erase(size_t index);
	void Sort() noexcept;
	void RSort() noexcept;
public: // вспопогательное
	template <typename S> friend std::ostream& operator<<(std::ostream& os, const Array<S>& array);
	template <typename S> friend bool operator==(const Array<S>& lhs, const Array<S>& rhs);
	template <typename S> friend bool operator!=(const Array<S>& lhs, const Array<S>& rhs);
private: // обмен содержимым
	void Swap(Array& tmp);
private:
	size_t _size;	// количество элементов
	T* _data;		// элементы
};

// исключение, индекс больше чем количество элементов
class OutOfRange : public std::out_of_range
{
public:
	OutOfRange(size_t index, size_t size)
		: std::out_of_range("out of range")
		, _msg("index " + std::to_string(index) + " is out of " + std::to_string(size))
	{}
public:
	const char* what() const noexcept override
	{
		return _msg.c_str();
	}
private:
	std::string _msg;

};

#include "Array.cpp"

