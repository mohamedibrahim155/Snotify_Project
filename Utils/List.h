#pragma once

#include <iostream>


template <typename T>
class List
{
public: 
	List();
	~List();	


private: 

	T* m_Array;
	size_t m_Capacity;
	size_t m_Size;


};

template<typename T>
  List<T>::List() : m_Array(nullptr), m_Capacity(0), m_Size(0)
{
}

 template<typename T>
  List<T>::~List()
 {
	  delete [] m_Array
 }
