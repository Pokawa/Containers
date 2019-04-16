//
// Created by pokawa on 16.04.2019.
//

#ifndef LIST_LIST_HPP
#define LIST_LIST_HPP

#include <iostream>
#include "list_iterator.hpp"

namespace cw
{
    template <class T>
    class List
    {
        typedef node<T> node;
        typedef unsigned long long int size_type;
        size_type siz{};
        node* point;

    public:
        typedef cw::ListIterator<T> Iterator;
        List();
        List(size_type, const T&);
        explicit List(size_type);
        List(std::initializer_list<T>);
        List(const List<T>&);
        template <class Iter>
        List(Iter, Iter);


        void pushBack(const T&);
        void pushFront(const T&);
        void popBack();
        void popFront();
        T& front();
        T& back();
        void remove(const T&);
        //TODO removeIf template <class Predicate>
        //void removeIf (Predicate pred);
        void resize(size_type);
        void reverse();
        size_type size() const;
        T&operator[](size_type);
        Iterator begin() const;
        Iterator end() const;
        bool empty();
        void clear();
        void erase(Iterator);
        void erase(Iterator, Iterator);
        void insert(size_type, const T&, Iterator);
        void insert(Iterator, const T&);
        void splice(Iterator, List<T>&);
        void splice(Iterator, List<T>&, Iterator);
        void splice(Iterator, List<T>&, Iterator, Iterator);
        template <class InputIterator>
        void insert(Iterator, InputIterator, InputIterator);
        void insert(Iterator, std::initializer_list<T>);
    };

    template<class T>
    List<T>::List() {
        siz = 0;
        point = new node{T(), nullptr, nullptr};
        point->next = point->previous = point;
    }

    template<class T>
    List<T>::List(size_type count, const T & value) : List(){
        while (count--)
            pushBack(value);
    }

    template<class T>
    List<T>::List(size_type count) : List(count, T()){
    }

    template<class T>
    template<class Iter>
    List<T>::List(Iter begin, Iter end) : List() {
        while (begin != end)
            pushBack(*(begin++));
    }

    template<class T>
    List<T>::List(std::initializer_list<T> in) : List(in.begin(), in.end()){
    }

    template<class T>
    List<T>::List(const List<T> & in) : List(in.begin(), in.end()){
    }

    template<class T>
    void List<T>::insert(List::Iterator position, const T & value) {
        position.data()->previous = position.data()->previous->next = new node{value, position.data(), position.data()->previous};
        siz++;
    }

    template<class T>
    void List<T>::pushBack(const T & value) {
        insert(end(), value);
    }

    template<class T>
    void List<T>::pushFront(const T & value) {
        insert(begin(), value);
    }

    template<class T>
    typename List<T>::Iterator List<T>::end() const {
        return cw::List<T>::Iterator(point);
    }

    template<class T>
    typename List<T>::Iterator List<T>::begin() const {
        return cw::List<T>::Iterator(point->next);
    }

    template<class T>
    T &List<T>::operator[](size_type index) {
        return *(begin() + index);
    }

    template<class T>
    typename List<T>::size_type List<T>::size() const {
        return siz;
    }

    template<class T>
    bool List<T>::empty() {
        return point->next == point;
    }

    //w ten sposb bo inaczej wywolywana jest funkcja
    // void List<T>::insert(List::Iterator position, InputIterator begin, InputIterator end)
    // dla T typu numerycznego
    // nie wiem jak to obejsc
    template<class T>
    void List<T>::insert(size_type count, const T & value, List::Iterator position) {
        if (count) {
            List<T> foo(count, value);
            splice(position, foo);
        }
    }

    template<class T>
    template<class InputIterator>
    void List<T>::insert(List::Iterator position, InputIterator begin, InputIterator end) {
        List<T> foo(begin, end);
        splice(position, foo);
    }

    template<class T>
    void List<T>::insert(List::Iterator position, std::initializer_list<T> in) {
        insert(position, in.begin(), in.end());
    }

    template<class T>
    void List<T>::splice(Iterator position, List<T>& in) {
        for (auto & a : in)
            insert(position, a);
        in.clear();
    }

    template<class T>
    void List<T>::splice(List::Iterator position, List<T>& in, List::Iterator i) {
        insert(position, *i);
        in.erase(i);
    }

    template<class T>
    void List<T>::splice(List::Iterator position, List<T> & in, List::Iterator begin, List::Iterator end) {
        insert(position, begin, end);
        in.erase(begin, end);
    }

    template<class T>
    void List<T>::erase(List::Iterator i) {
        i.data()->previous->next = i.data()->next;
        i.data()->next->previous = i.data()->previous;
        delete i.data();
        siz--;
    }

    template<class T>
    void List<T>::erase(List::Iterator begin, List::Iterator end) {
        begin.data()->previous->next = end.data();
        end.data()->previous = begin.data()->previous;
        while (begin != end) {
            auto tmp = begin.data();
            begin++;
            delete tmp;
            siz--;
        }
    }

    template<class T>
    void List<T>::clear() {
        erase(begin(), end());
    }

    template<class T>
    T &List<T>::front() {
        return *begin();
    }

    template<class T>
    T &List<T>::back() {
        return *(end() - 1);
    }

    template<class T>
    void List<T>::popBack() {
        erase(end() - 1);
    }

    template<class T>
    void List<T>::popFront() {
        erase(begin());
    }

    template<class T>
    void List<T>::remove(const T & value) {
        for (auto i = begin(); i != end();)
            if ((i++).data()->value == value)
                erase(i-1);

    }

    template<class T>
    void List<T>::resize(List::size_type newSize) {
        if (newSize < siz)
            erase(begin()+newSize, end());
        else
        while (siz != newSize)
            pushBack(T());
    }

    template<class T>
    void List<T>::reverse() {
     for (auto i = begin(); i != end(); )
     {
         auto tmp = i + 1;
         i.data()->next = (i - 1).data();
         i.data()->previous = tmp.data();
         i = tmp;
     }
     std::swap(point->next, point->previous);
    }


}


#endif //LIST_LIST_HPP
