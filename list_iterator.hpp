//
// Created by pokawa on 12.04.2019.
//

#ifndef VECT_LIST_ITERATOR_HPP
#define VECT_LIST_ITERATOR_HPP

#include "list.hpp"

namespace cw
{
    template <class T>
    class ListIterator
    {
        struct node
        {
            T value;
            node* next;
            node* previous;
        };
        node*ptr;

    public:
        explicit ListIterator( void*);
        ListIterator(const ListIterator<T>&);
        ListIterator<T>&operator++();
        const ListIterator<T> operator++(int);
        ListIterator<T>&operator--();
        const ListIterator<T> operator--(int);
        T&operator*() const;
        T&operator[](const std::size_t&) const;
        T&operator->() const;
        ListIterator<T> operator+(const std::size_t&) const;
        ListIterator<T> operator-(const std::size_t&) const;
        std::size_t operator-(const ListIterator<T>&) const;
        void operator+=(const std::size_t&);
        void operator-=(const std::size_t&);
        bool operator==(const ListIterator<T>&) const;
        bool operator!=(const ListIterator<T>&) const;
        bool operator<(const ListIterator<T>&) const;
        bool operator<=(const ListIterator<T>&) const;
        bool operator>(const ListIterator<T>&) const;
        bool operator>=(const ListIterator<T>&) const;
    };

    template<class T>
    ListIterator<T>::ListIterator( void* ptr) {
        this->ptr = (node*)ptr;
    }

    template<class T>
    ListIterator<T> &ListIterator<T>::operator++() {
        ptr = ptr->next;
        return *this;
    }

    template<class T>
    const ListIterator<T> ListIterator<T>::operator++(int) {
        ListIterator<T> foo = *this;
        ptr = ptr->next;
        return foo;
    }

    template<class T>
    ListIterator<T> &ListIterator<T>::operator--() {
        ptr = ptr->previous;
        return *this;
    }

    template<class T>
    const ListIterator<T> ListIterator<T>::operator--(int) {
        ListIterator<T> foo = *this;
        ptr = ptr->previous;
        return foo;
    }

    template<class T>
    T &ListIterator<T>::operator*() const {
        return ptr->value;
    }

    template<class T>
    T &ListIterator<T>::operator[](const std::size_t & index) const{
        return *(*this + index);
    }

    template<class T>
    T &ListIterator<T>::operator->() const{
        return ptr->value;
    }

    template<class T>
    ListIterator<T> ListIterator<T>::operator+(const std::size_t& in) const{
        ListIterator<T> foo = *this;
        for (std::size_t i = 0; i < in; ++i)
            foo++;
        return foo;
    }

    template<class T>
    ListIterator<T> ListIterator<T>::operator-(const std::size_t &in) const{
        ListIterator<T> foo = *this;
        for (std::size_t i = 0; i < in; ++i)
            foo--;
        return foo;
    }

    template<class T>
    void ListIterator<T>::operator+=(const std::size_t & in) {
        for (std::size_t i = 0; i < in; ++i)
            *(this)++;
    }

    template<class T>
    void ListIterator<T>::operator-=(const std::size_t & in) {
        for (std::size_t i = 0; i < in; ++i)
            *(this)--;
    }

    template<class T>
    bool ListIterator<T>::operator==(const ListIterator<T> & in) const{
        return ptr == in.ptr;
    }

    template<class T>
    bool ListIterator<T>::operator!=(const ListIterator<T> & in) const{
        return ptr != in.ptr;
    }

    template<class T>
    bool ListIterator<T>::operator<(const ListIterator<T> & in) const{
        return ptr < in.ptr;
    }

    template<class T>
    bool ListIterator<T>::operator<=(const ListIterator<T> &in) const{
        return ptr <= in.ptr;
    }

    template<class T>
    bool ListIterator<T>::operator>(const ListIterator<T> & in) const{
        return ptr > in.ptr;
    }

    template<class T>
    bool ListIterator<T>::operator>=(const ListIterator<T> & in) const{
        return ptr >= in.ptr;
    }

    template<class T>
    std::size_t ListIterator<T>::operator-(const ListIterator<T> & in) const {
        std::size_t i = 0;
        for (ListIterator<T> foo = *this; foo != in; i++, foo--);
        return i;
    }

    template<class T>
    ListIterator<T>::ListIterator(const ListIterator<T> & in) {
        ptr = in.ptr;
    }
}


#endif //VECT_LIST_ITERATOR_HPP
