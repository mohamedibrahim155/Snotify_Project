#pragma once

#include <iostream>

namespace RIO_UTILS
{
	template <typename T>
	class List
	{
	public:
		List();
		List(size_t intiaSize);
		List& operator=(const List& other);
		~List();

		void Add(const T& value);
		void Remove(const T& value);
		void RemoveAt(size_t index);
		void Clear();
		void Insert(size_t index, const T& value);
		void Sort();
		void CompareSort(bool (*compare)(const T&, const T&));

		bool IsEmpty() const;

		size_t GetLength();

		T& GetAt(size_t index);
		T& operator[](size_t index)
		{
			if (index >= size)
			{
				std::cout << "Index out of bound" << std::endl;
			}
			return data[index];

		}
		T& GetLast();
		T& GetFirst();


	private:

		T* data;
		size_t capacity;
		size_t size;

		void Resize();
		void Swap(T& a, T& b);

	};

	template<typename T>
	List<T>::List() : data(nullptr), capacity(0), size(0)
	{
	}

	template<typename T>
	inline List<T>::List(size_t intialSize) : data(nullptr), capacity(intialSize), size(intialSize)
	{
		data = new T[capacity];
	}

	template<typename T>
	List<T>& List<T>::operator=(const List& other)
	{
		if (this != &other)
		{
			delete[] data;
			capacity = other.capacity;
			size = other.size;
			data = new T[capacity];
			for (size_t i = 0; i < size; i++)
			{
				data[i] = other.data[i];
			}
		}
		return *this;
	}

	template<typename T>
	List<T>::~List()
	{
		delete[] data;
		data = nullptr;
	}

	template<typename T>
	inline void List<T>::Add(const T& value)
	{
		if (size == capacity)
		{
			Resize();
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

	template<typename T>
	inline T& List<T>::GetLast()
	{
		return data[size - 1];
	}

	template<typename T>
	inline T& List<T>::GetFirst()
	{
		return data[0];
	}

	template<typename T>
	inline void List<T>::Resize()
	{
		capacity = (capacity == 0) ? 1 : capacity * 2;

		T* newTempData = new T[capacity];

		for (size_t i = 0; i < size; ++i) {
			newTempData[i] = data[i];
		}

		delete[] data;
		data = newTempData;
	}
	template<typename T>
	inline void List<T>::Swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}



	template <typename T>
	inline void List<T>::RemoveAt(size_t index)
	{
		if (index < size)
		{
			for (size_t i = index; i < size - 1; i++)
			{
				data[i] = data[i + 1];
			}
			size--;
		}

		// Removes the 
	}

	template<typename T>
	inline void List<T>::Clear()
	{
		delete[] data;
		data = nullptr;
		capacity = 0;
		size = 0;

		// Deleting all the values stored
	}

	template<typename T>
	inline void List<T>::Insert(size_t index, const T& value)
	{
		if (index <= size)
		{
			if (size == capacity)
			{
				Resize();
			}

			for (size_t i = size; i > index; i--)
			{
				data[i] = data[i - 1];
			}

			data[index] = value;
			size++;
		}
	}
	template<typename T>
	inline void List<T>::Sort()
	{
		// using bubble sort here
		for (size_t i = 0; i < size - 1; i++)
		{
			for (size_t j = 0; j < size - i - 1; j++)
			{
				if (data[j] > data[j + 1])
				{
					//T* temp = data[j];
					//data[j] = data[j + 1];

					//data[j + 1] = temp;

					Swap(data[j], data[j + 1]);
				}
			}
		}
	}

	template<typename T>
	inline void List<T>::CompareSort(bool(*compare)(const T&, const T&))
	{
		for (size_t i = 0; i < size - 1; i++)
		{
			for (size_t j = 0; j < size - i - 1; j++)
			{
				if (compare(data[j], data[j + 1]))
				{
					Swap(data[j], data[j + 1]);
				}
			}
		}
	}

	template<typename T>
	inline bool List<T>::IsEmpty() const
	{
		return size == 0;
	}
}