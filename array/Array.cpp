#include "Array.h"	

#include <cstring>

// Реализация Array

//
// Создание и удаление
//

template <typename T>
Array<T>::Array()
		: _size{}
		, _data{}
{}
 
template <typename T>
Array<T>::Array(size_t size)
		: _size(size)
		, _data(new T[_size])
{}

template <typename T>
Array<T>::Array(std::initializer_list<T> l)
	: _size(l.size())
	, _data(new T[_size])
{
	size_t i = 0;
	for (auto item : l) {
		if (i < _size) {
			_data[i++] = item;
		}
		else {
			break;
		}
	}
}

template <typename T>
Array<T>::Array(const Array<T>& other)
	: _size(other._size)
	, _data(new T[_size])
{
	// memcpy(_data, other._data, _size * sizeof(T));
	for (size_t i = 0; i < _size; ++i) {
		_data[i] = other._data[i];
	}
}

template <typename T>
Array<T>::~Array()
{
	delete[] _data;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
	Array tmp(other);
	Swap(tmp);
	return *this;
}

//
// Доступ к элементам  
// 

// получение размера массива
template <typename T>
size_t Array<T>::GetSize() const noexcept
{
	return _size;
}

// доступ к элементу по индексу
template <typename T>
T& Array<T>::operator[] (size_t index)
{
	if (index >= _size) {
		throw OutOfRange(index, _size);
	}
	return _data[index];

}

// доступ к элементу по индексу
template <typename T>
const T& Array<T>::operator[] (size_t index) const
{
	return const_cast<Array<T>*>(this)->operator[](index);
}

// Получить первый элемент массива с индексом 0
template <typename T>
const T& Array<T>::GetFront() const
{
	if (_size == 0) {
		throw OutOfRange(0, _size);
	}
	return _data[0];
}

// Получить элемент с индексом size - 1
template <typename T>
const T& Array<T>::GetBack() const
{
	if (_size == 0) {
		throw OutOfRange(0, _size);
	}
	return _data[_size - 1];
}

// поиска в контейнере элемента по индексу
template <typename T>
bool Array<T>::Find(int value, size_t& index) const noexcept
{
	for (size_t i = 0; i < _size; ++i) {
		if (_data[i] == value) {
			index = i;
			return true;
		}
	}
	return false;
}

//
// Изменение массива
//

// Меняет размер массива
// в большую сторону с сохранением всех данных
// в меньшую сторону с сохранением остающихся данных
template <typename T>
void Array<T>::Resize(size_t size)
{
	Array tmp(size);

	size_t nbytes = (size < _size ? size : _size);// *sizeof(T);
	// memcpy(tmp._data, _data, nbytes);
	for (size_t i = 0; i < nbytes; ++i) {
		tmp._data[i] = _data[i];
	}

	Swap(tmp);
}

// добавить элемент в начало массива
// происходит копирование всех элементов
template <typename T>
void Array<T>::PushFront(const T& value)
{
	Array tmp(_size + 1);

	// size_t nbytes = _size;// *sizeof(T);

	tmp._data[0] = value;

	// memcpy(tmp._data + 1, _data, nbytes);
	for (size_t i = 1; i < _size + 1; ++i) {
		tmp._data[i] = _data[i - 1];
	}

	Swap(tmp);
}

// удалить элемент из начала массива
// происходит копирование всех элементов
template <typename T>
void Array<T>::PopFront()
{
	Erase(0);
}

// добавить элемент в конец массива 
// происходит копирование всех элементов
template <typename T>
void Array<T>::PushBack(const T& value)
{
	if (_size == 0) {
		PushFront(value);
	} else {
		Insert(value, _size - 1);
	}
}

// Удалить элемент с конца массива  
// происходит копирование всех элементов
template <typename T>
void Array<T>::PopBack()
{
	Erase(_size - 1);
}

// вставить элемент в массив после элемента по заданному индексу
// происходит копирование всех элементов
template <typename T>
void Array<T>::Insert(const T& value, size_t index)
{
	if (index >= _size) {
		throw OutOfRange(index, _size);
	}

	Array<T> tmp(_size + 1);

	tmp._data[index + 1] = value;

	// memcpy(tmp._data, _data, (index + 1) * sizeof(int));
	for (size_t i = 0; i < index + 1; ++i) {
		tmp._data[i] = _data[i];
	}

	if (index < _size - 1) {
		// memcpy(tmp._data + index + 2, _data + index + 1, (_size - index - 1) * sizeof(int));
		for (size_t i = index + 2; i < _size + 1; ++i) {
			tmp._data[i] = _data[i - 1];
		}
	}

	Swap(tmp);
}

// удалить элемент по заданному индексу
// происходит копирование всех элементов
template <typename T>
void Array<T>::Erase(size_t index)
{
	if (index >= _size) {
		throw OutOfRange(index, _size);
	}

	Array<T> tmp(_size - 1);

	if (index > 0) {
		// memcpy(tmp._data, _data, (index + 1 - 1) * sizeof(int));
		for (size_t i = 0; i < index + 1 - 1; ++i) {
			tmp._data[i] = _data[i];
		}
	}
	if (index < _size - 1) {
		// memcpy(tmp._data + index, _data + index + 1, (tmp._size - index) * sizeof(int));
		for (size_t i = index; i < _size - 1; ++i) {
			tmp._data[i] = _data[i + 1];
		}
	}

	Swap(tmp);
}

// сортировка в порядке возрастания
template <typename T>
void Array<T>::Sort() noexcept
{
	for (size_t i = 0; i < _size - 1; ++i) {
		for (size_t j = 0; j < _size - i - 1; ++j) {
			if (_data[j] > _data[j + 1]) {
				std::swap(_data[j], _data[j + 1]);
			}
		}
	}

}

// сортировка в порядке убывания
template <typename T>
void Array<T>::RSort() noexcept
{
	for (size_t i = 0; i < _size - 1; ++i) {
		for (size_t j = 0; j < _size - 1 - i; ++j) {
			if (_data[j] < _data[j + 1]) {
				std::swap(_data[j], _data[j + 1]);
			}
		}
	}

}

// 
// Вспомогательные методы 
//

// вывод содержимого массива
template <typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& array)
{
	for (size_t i = 0; i < array._size; ++i) {
		os << array._data[i] << " ";
	}

	return os;
}

// проверка на равенство массивов
template <typename T>
bool operator==(const Array<T>& lhs, const Array<T>& rhs)
{
	if (lhs._size != rhs._size) {
		return false;
	}

	for (size_t i = 0; i < lhs._size; ++i) {
		if (lhs._data[i] != rhs._data[i]) {
			return false;
		}
	}

	return true;
}

// проверка на неравенство массивов
template <typename T>
bool operator!=(const Array<T>& lhs, const Array<T>& rhs)
{
	return !(lhs == rhs);
}

//
// Закрытые методы 
//

// обмен содержанием между массивами
template <typename T>
void Array<T>::Swap(Array<T>& tmp)
{
	std::swap(_size, tmp._size);
	std::swap(_data, tmp._data);
}



