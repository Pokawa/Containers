//
// Created by pokawa on 05.04.2019.
//

#ifndef VECT_VECTOR_HPP
#define VECT_VECTOR_HPP

#include "iterators.hpp"

namespace cw
{

    template <class T>
    class vector
    {
    private:
        T* first;
        T* last;
        T* verylast;

    public:
        typedef RandomAccessIterator<T> iterator;

        vector();
        ~vector();
        explicit vector(const std::size_t &);
        explicit vector(const std::size_t &, const T&);
        vector(std::initializer_list<T>);
        vector(const vector&);

        void resize(const std::size_t&);
        void reserve(const std::size_t&);
        void shrinkToFit();
        T& front();
        T& back();
        void swap(vector &);
        void clear();
        T* data();
        void pushBack(const T&);

        void insert(iterator, const T&);
        void insert(iterator, const std::initializer_list<T>&);
        void insert(iterator, const std::size_t&, const T&);
        void popBack();
        T& at(const std::size_t&);
        T&operator[](const std::size_t&);
        std::size_t size();
        std::size_t capacity();
        iterator begin();
        iterator end();
    };

    template<class T>
    vector<T>::vector() {
        first = last = verylast = nullptr;
    }

    template<class T>
    vector<T>::vector(const std::size_t & size) : vector() {
        resize(size);
    }

    template<class T>
    vector<T>::vector(const std::size_t & size,const T & value) : vector(){
        resize(size);
        for (std::size_t i = 0; i < size; i++)
            *(first + i) = value;
    }

    template<class T>
    void vector<T>::resize(const std::size_t & newSize) {
        if (newSize > capacity()) reserve(newSize);
        for (std::size_t i = size() - 1; i <= newSize - 1; ++i)
            first[i] = T();
        last = first + newSize - 1;
    }

    template<class T>
    vector<T>::vector(const std::initializer_list<T> list) : vector() {
        resize(list.size());
        for (std::size_t i = 0; i < list.size(); i++)
            *(first + i) = *(list.begin() + i);
    }

    template<class T>
    vector<T>::vector(const vector & in) {
        allocate(in.size());
    }

    template<class T>
    std::size_t vector<T>::size() {
        return first == last ? 0 : last - first + 1;
    }

    template<class T>
    std::size_t vector<T>::capacity() {
        return first == verylast ? 0 : verylast - first + 1;
    }

    template<class T>
    T &vector<T>::operator[](const std::size_t& index) {
        return *(first + index);
    }

    template<class T>
    void vector<T>::reserve(const std::size_t & newSize) {
        if (newSize <= size())
            return;
        T* buff = first;
        first = new T[newSize];
        for (std::size_t i = 0; buff + i <= last && buff != nullptr; ++i)
            first[i] = buff[i];
        verylast = first + newSize - 1;
        last = first + (last - buff);
        delete[] buff;
    }

    template<class T>
    void vector<T>::pushBack(const T & value) {
        if (last == verylast)
            reserve(size() == 0 ? 1 : size()*2);
        *(++last) = value;
    }

    template<class T>
    void vector<T>::popBack() {
        resize(size() - 1);
    }

    template<class T>
    T &vector<T>::at(const std::size_t& index) {
        return this[index];
    }

    template<class T>
    typename vector<T>::iterator vector<T>::begin() {
        return cw::vector<T>::iterator(first);
    }

    template<class T>
    typename vector<T>::iterator vector<T>::end() {
        return first == last ? begin() : cw::vector<T>::iterator(last + 1);
    }

    template<class T>
    void vector<T>::shrinkToFit() {
        if (capacity() == size())
            return;
        T* buff = first;
        first = new T[size()];
        for (std::size_t i = 0; buff + i <= last; ++i)
            first[i] = buff[i];
        verylast = last = first + (last - buff) ;
        delete[] buff;
    }

    template<class T>
    T &vector<T>::front() {
        return *first;
    }

    template<class T>
    T &vector<T>::back() {
        return *last;
    }

    template<class T>
    void vector<T>::swap(vector & in) {
        std::swap(first, in.first);
        std::swap(last, in.last);
        std::swap(verylast, in.verylast);
    }

    template<class T>
    void vector<T>::clear() {
        delete[] first;
        vector();
    }

    template<class T>
    T *vector<T>::data() {
        return first;
    }

    template<class T>
    void vector<T>::insert(iterator index, const T & value) {
        insert(index, 1, value);
    }

    template<class T>
    void vector<T>::insert(iterator index, const std::size_t & amount, const T & value) {
        std::size_t i = index - begin();
        while (last + amount > verylast)
            reserve(capacity()*2);
        for (std::size_t a = size() - 1; a + 1 >= i + 1; --a)
            first[a + amount] = first[a];
        for (std::size_t a = i; a < i + amount; a++)
            first[a] = value;
        last += amount;
    }

    template<class T>
    void vector<T>::insert(iterator index, const std::initializer_list<T> & values) {
        std::size_t i = index - begin();
        while (last + values.size() > verylast)
            reserve(capacity()*2);
        for (std::size_t a = size() - 1; a >= i; --a)
            first[a + values.size()] = first[a];
        for (std::size_t a = i; a < i + values.size(); a++)
            first[a] = *(values.begin() + a - i);
        last += values.size();
    }

    template<class T>
    vector<T>::~vector() {
        delete[] first;
    }
}


#endif //VECT_VECTOR_HPP
