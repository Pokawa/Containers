//
// Created by pokawa on 08.04.2019.
//

#ifndef RA_iTERATOR_HPP
#define RA_ITERATOR_HPP


namespace cw
{
    template <class T>
    class RandomAccessIterator
    {
        T* ptr;
    public:
        explicit RandomAccessIterator( T*);
        RandomAccessIterator(const RandomAccessIterator<T>&);
        RandomAccessIterator<T>&operator++();
        const RandomAccessIterator<T> operator++(int);
        RandomAccessIterator<T>&operator--();
        const RandomAccessIterator<T> operator--(int);
        T&operator*() const;
        T&operator[](const std::size_t&) const;
        T&operator->() const;
        RandomAccessIterator<T> operator+(const std::size_t&) const;
        RandomAccessIterator<T> operator-(const std::size_t&) const;
        std::size_t operator-(const RandomAccessIterator<T>&) const;
        void operator+=(const std::size_t&);
        void operator-=(const std::size_t&);
        bool operator==(const RandomAccessIterator<T>&) const;
        bool operator!=(const RandomAccessIterator<T>&) const;
        bool operator<(const RandomAccessIterator<T>&) const;
        bool operator<=(const RandomAccessIterator<T>&) const;
        bool operator>(const RandomAccessIterator<T>&) const;
        bool operator>=(const RandomAccessIterator<T>&) const;
    };

    template<class T>
    RandomAccessIterator<T>::RandomAccessIterator( T * ptr) {
        this->ptr = ptr;
    }

    template<class T>
    RandomAccessIterator<T> &RandomAccessIterator<T>::operator++() {
        ptr++;
        return *this;
    }

    template<class T>
    const RandomAccessIterator<T> RandomAccessIterator<T>::operator++(int) {
        RandomAccessIterator<T> foo = *this;
        ptr++;
        return foo;
    }

    template<class T>
    RandomAccessIterator<T> &RandomAccessIterator<T>::operator--() {
        ptr--;
        return *this;
    }

    template<class T>
    const RandomAccessIterator<T> RandomAccessIterator<T>::operator--(int) {
        RandomAccessIterator<T> foo = this;
        ptr--;
        return foo;
    }

    template<class T>
    T &RandomAccessIterator<T>::operator*() const {
        return *ptr;
    }

    template<class T>
    T &RandomAccessIterator<T>::operator[](const std::size_t & index) const{
        return *(ptr + index);
    }

    template<class T>
    T &RandomAccessIterator<T>::operator->() const{
        return *ptr;
    }

    template<class T>
    RandomAccessIterator<T> RandomAccessIterator<T>::operator+(const std::size_t& in) const{
        return RandomAccessIterator<T>(ptr + in);
    }

    template<class T>
    RandomAccessIterator<T> RandomAccessIterator<T>::operator-(const std::size_t &in) const{
        return RandomAccessIterator<T>(ptr - in);
    }

    template<class T>
    void RandomAccessIterator<T>::operator+=(const std::size_t & in) {
        ptr += in;
    }

    template<class T>
    void RandomAccessIterator<T>::operator-=(const std::size_t & in) {
        ptr -= in;
    }

    template<class T>
    bool RandomAccessIterator<T>::operator==(const RandomAccessIterator<T> & in) const{
        return ptr == in.ptr;
    }

    template<class T>
    bool RandomAccessIterator<T>::operator!=(const RandomAccessIterator<T> & in) const{
        return ptr != in.ptr;
    }

    template<class T>
    bool RandomAccessIterator<T>::operator<(const RandomAccessIterator<T> & in) const{
        return ptr < in.ptr;
    }

    template<class T>
    bool RandomAccessIterator<T>::operator<=(const RandomAccessIterator<T> &in) const{
        return ptr <= in.ptr;
    }

    template<class T>
    bool RandomAccessIterator<T>::operator>(const RandomAccessIterator<T> & in) const{
        return ptr > in.ptr;
    }

    template<class T>
    bool RandomAccessIterator<T>::operator>=(const RandomAccessIterator<T> & in) const{
        return ptr >= in.ptr;
    }

    template<class T>
    std::size_t RandomAccessIterator<T>::operator-(const RandomAccessIterator<T> & in) const {
        return ptr - in.ptr;
    }

    template<class T>
    RandomAccessIterator<T>::RandomAccessIterator(const RandomAccessIterator<T> & in) {
        ptr = in.ptr;
    }
}
#endif //RA_ITERATOR_HPP
