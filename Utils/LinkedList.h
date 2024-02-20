#pragma once
#include <iostream>

namespace RIO_UTILS {
    template <typename T>
    class Node
    {
    public:
        T data;
        Node* prev;
        Node* next;

        Node(T value) : data(value), prev(nullptr), next(nullptr) {}
    };

    template <typename T>
    class LinkedList
    {
    public:
        LinkedList();
        LinkedList(const LinkedList& other);
        LinkedList& operator=(const LinkedList& other);
        ~LinkedList();

        void InsertBeforeCurrent(T value);
        void DeleteAtCurrent();
        void MoveNext();
        void MovePrevious();
        void MoveToFirst();
        void MoveToLast();

        bool IsEmpty() const;
        void Clear();
        void Display() const;

        Node<T>* GetCurrentNode() const;
        Node<T>* GetTailNode() const;
        Node<T>* GetHeadNode() const;

        unsigned int GetSize() const;

    private:

        Node<T>* head;
        Node<T>* tail;
        Node<T>* current;
        unsigned int size = 0;
    };

    template<typename T>
    inline LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), current(nullptr) {}

    template<typename T>
    inline LinkedList<T>::LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), current(nullptr)
    {
        Node<T>* otherCurrent = other.head;
        while (otherCurrent)
        {
            InsertBeforeCurrent(otherCurrent->data);
            otherCurrent = otherCurrent->next;
        }
    }


    template<typename T>
    inline LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other)
    {
        if (this != &other)
        {
            Clear();
            Node<T>* otherCurrent = other.head;
            while (otherCurrent)
            {
                InsertBeforeCurrent(otherCurrent->data);
                otherCurrent = otherCurrent->next;
            }
        }
        return *this;
    }


    template<typename T>
    inline LinkedList<T>::~LinkedList()
    {
        Clear();
    }

    template<typename T>
    inline void LinkedList<T>::InsertBeforeCurrent(T value)
    {
        Node<T>* newNode = new Node<T>(value);

        if (current == nullptr)
        {
            head = tail = current = newNode;
        }
        else
        {
            newNode->prev = current->prev;
            newNode->next = current;
            if (current->prev != nullptr)
            {
                current->prev->next = newNode;
            }
            else
            {
                head = newNode;
            }
            current->prev = newNode;
        }

        size++;
    }

    template<typename T>
    inline void LinkedList<T>::DeleteAtCurrent()
    {
        if (current != nullptr)
        {
            if (current->prev != nullptr)
            {
                current->prev->next = current->next;
            }
            else
            {
                head = current->next;
            }

            if (current->next != nullptr)
            {
                current->next->prev = current->prev;
            }
            else
            {
                tail = current->prev;
            }

            delete current;
            current = nullptr;

            size--;
        }
    }

    template<typename T>
    inline void LinkedList<T>::MoveNext()
    {
        if (current != nullptr && current->next != nullptr)
        {
            current = current->next;
        }
    }

    template<typename T>
    inline void LinkedList<T>::MovePrevious()
    {
        if (current != nullptr && current->prev != nullptr)
        {
            current = current->prev;
        }
    }

    template<typename T>
    inline void LinkedList<T>::MoveToFirst()
    {
        current = head;
    }

    template<typename T>
    inline void LinkedList<T>::MoveToLast()
    {
        current = tail;
    }

    template<typename T>
    inline Node<T>* LinkedList<T>::GetCurrentNode() const
    {
        return current;
    }

    template<typename T>
    inline Node<T>* LinkedList<T>::GetTailNode() const
    {
        return tail;
    }

    template<typename T>
    inline Node<T>* LinkedList<T>::GetHeadNode() const
    {
        return head;
    }

    template<typename T>
    inline unsigned int LinkedList<T>::GetSize() const
    {
        return size;
    }

    template<typename T>
    inline bool LinkedList<T>::IsEmpty() const
    {
        return head == nullptr;
    }

    template<typename T>
    inline void LinkedList<T>::Clear()
    {
        while (head)
        {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = current = nullptr;
    }

    template<typename T>
    inline void LinkedList<T>::Display() const
    {
        Node<T>* temp = head;
        while (temp)
        {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
}