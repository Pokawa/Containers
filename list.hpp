//
// Created by pokawa on 12.04.2019.
//

#ifndef VECT_LIST_HPP
#define VECT_LIST_HPP

#include <iostream>
#include "list_iterator.hpp"

namespace cw
{
    template <class T>
    class List
    {
        struct node
        {
            T value;
            node* next;
            node* previous;
        };

        std::size_t siz;
        node* first;
        node* last;

    public:
        typedef cw::ListIterator<T> Iterator;
        List();
        List(std::size_t, const T&);
        explicit List(std::size_t);
        List(std::initializer_list<T>);
        List(const List<T>&);
        template <class Iter>
                List(Iter, Iter);

        void pushBack(const T&);
        void pushFront(const T&);
        std::size_t size() const;
        T&operator[](std::size_t);
        Iterator begin() const;
        Iterator end() const;
    };

    template<class T>
    template<class Iter>
    List<T>::List(Iter begin, Iter end) {
        siz = (end - 1) - begin;
        first = last = new node{*(begin++), nullptr, nullptr};
        for (std::size_t i = siz; i; i--)
        {
            last->next = new node{*(begin++), nullptr, last};
            last = last->next;
        }
        last->next = new node{T(), first, last};
        first->previous = last->next;
    }

    template<class T>
    List<T>::List() {
        first = last = nullptr;
    }

    template<class T>
    List<T>::List(std::size_t amount, const T & value) {
        first = last = new node{value, nullptr, nullptr};
        for (; amount; amount--) {
            last->next = new node{value, nullptr, last};
            last = last->next;
        }
        last->next = new node{T(), first, last};
        first->previous = last->next;
        siz = amount;
    }

    template<class T>
    List<T>::List(std::initializer_list<T> ilist) {
        first = last = new node{*(ilist.begin()), nullptr, nullptr};
        for (std::size_t i = 1; i < ilist.size(); i++) {
            last->next = new node{*(ilist.begin() + i), nullptr, last};
            last = last->next;
        }
        last->next = new node{T(), first, last};
        first->previous = last->next;
        siz = ilist.size();
    }



    template<class T>
    List<T>::List(const List<T> & in) :List(in.begin(), in.end()){
    }

    template<class T>
    T &List<T>::operator[](std::size_t index) {
        return *(begin() + index);
    }

    template<class T>
    List<T>::List(std::size_t size) : List(size, T()){}

    template<class T>
    typename List<T>::Iterator List<T>::begin() const{
        return cw::List<T>::Iterator(first);
    }

    template<class T>
    typename List<T>::Iterator List<T>::end() const{
        return cw::List<T>::Iterator(last->next);    }

    template<class T>
    void List<T>::pushBack(const T & value) {
        last = last->next;
        last->value = value;
        last->next = new node{T(), first, last};
        siz++;
    }

    template<class T>
    void List<T>::pushFront(const T & value) {
        first = last->next->next = new node{value, first, last->next};
        first->next->previous = first;
        siz++;
    }

    template<class T>
    std::size_t List<T>::size() const{
        return siz;
    }
}

#endif //VECT_LIST_HPP
