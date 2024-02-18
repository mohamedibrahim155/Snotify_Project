#pragma once

#include <iostream>


template <typename T>
class List
{
public: 
	List();
	~List();	

	void Add(const T& value);
	void Remove(const T& value);
	void RemoveAt(size_t index);
	void Insert(size_t index, const T& value);
	size_t GetLength();

	T& GetAt(size_t index);
	T& operator[](size_t index)
	{


		if (index >= size)
		{
			std::cout << "Index out of bounds" << std::endl;
		}
		return data[index];

	}

	
private: 

	T* data;
	size_t capacity;
	size_t size;


};

template<typename T>
  List<T>::List() : data(nullptr), capacity(0), size(0)
{
}

 template<typename T>
  List<T>::~List()
 {
	  delete[] data;
 }

  template<typename T>
  inline void List<T>::Add(const T& value)
  {
	  if (size == capacity)
	  {
		  capacity = (capacity == 0) ? 1 : capacity * 2;

		  T* newTempData = new T[capacity];

		  for (int i = 0; i < size; i++)
		  {
			  newTempData[i] = data[i];
		  }

		  delete[] data;

		  data = newTempData;
	  }


	  data[size] = value;
	  size++;
  }

  template<typename T>
  inline void List<T>::Remove(const T& value)
  {
	  int removeIndex = 0;

	  while (removeIndex < size && data[removeIndex] != value)
	  {
		  removeIndex++;
	  }

	  if (removeIndex < size)
	  {
		  for (size_t i = removeIndex; i < size - 1; i++) 
		  {
			  data[i] = data[i + 1];
		  }
		  size--;
	  }
  }

  template<typename T>
  inline size_t List<T>::GetLength()
  {
	  return size;
  }

  template<typename T>
  inline T& List<T>::GetAt(size_t index)
  {
	  if (index >= size)
	  {
		  std::cout << "Index out of bounds" << std::endl;
	  }
	  return data[index];
  }

  template <typename T>
  inline void List<T>::RemoveAt(size_t index)
  {
	  if (index < size)
	  {
		  for (size_t i = index; i < size - 1; ++i)
		  {
			  data[i] = data[i + 1];
		  }
		  --size;
	  }
  }

  template<typename T>
  inline void List<T>::Insert(size_t index, const T& value)
  {
	  if (index <= size)
	  {
		  if (size == capacity)
		  {
			  capacity = (capacity == 0) ? 1 : capacity * 2;

			  T* newTempData = new T[capacity];

			  for (size_t i = 0; i < index; ++i)
			  {
				  newTempData[i] = data[i];
			  }

			  newTempData[index] = value;   // inserted value

			  for (size_t i = index + 1; i <= size; ++i) 
			  {
				  newTempData[i] = data[i - 1];
			  }

			  delete[] data;

			  data = newTempData;
			  size++;
		  }
		  else
		  {
			  for (size_t i = size; i > index; --i)
			  {
				  data[i] = data[i - 1];
			  }

			  data[index] = value;
			  size++;
		  }
	  }
  }