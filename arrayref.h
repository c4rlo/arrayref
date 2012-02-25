#ifndef INCLUDED_ARRAYREF
#define INCLUDED_ARRAYREF 

#include <vector>
#include <stdexcept>
#include <iterator>

template<class T>
class ArrayRef
{
public:

    inline ArrayRef();

    inline ArrayRef(const ArrayRef& other);

    template<size_t Size>
    inline ArrayRef(T (&array)[Size]);

    inline ArrayRef(T* begin, T* end);

    inline ArrayRef(std::vector<T>& vec);

    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<T*> reverse_iterator;
    typedef std::reverse_iterator<const T*> const_reverse_iterator;

    inline T* begin();
    inline const T* begin() const;
    inline T* end();
    inline const T* end() const;

    inline reverse_iterator rbegin();
    inline const_reverse_iterator rbegin() const;
    inline reverse_iterator rend();
    inline const_reverse_iterator rend() const;

    inline T& front();
    inline const T& front() const;
    inline T& back();
    inline const T& back() const;

    inline size_t size() const;
    inline bool empty() const;

    inline T& operator [] (size_t index);
    inline const T& operator [] (size_t index) const;

    inline T& at(size_t index);
    inline const T& at(size_t index) const;

private:
    // NOT IMPLEMENTED
    inline ArrayRef& operator = (const ArrayRef& other);

private:
    T *const d_begin;
    T *const d_end;
};

template<class T>
ArrayRef<T>
makeArrayRef(T* begin, T* end)
{
    return ArrayRef<T>(begin, end);
}

template<class T, size_t Size>
ArrayRef<T>
makeArrayRef(T (&array)[Size])
{
    return ArrayRef<T>(array);
}

template<class T>
ArrayRef<T>
makeArrayRef(std::vector<T>& vec)
{
    return ArrayRef<T>(vec);
}

template<class T>
ArrayRef<T>::ArrayRef()
: d_begin(0),
  d_end(0)
{
}

template<class T>
ArrayRef<T>::ArrayRef(const ArrayRef& other)
: d_begin(other.d_begin),
  d_end(other.d_end)
{
}

template<class T>
template<size_t Size>
ArrayRef<T>::ArrayRef(T (&array)[Size])
: d_begin(&array[0]),
  d_end(&array[Size])
{
}

template<class T>
ArrayRef<T>::ArrayRef(std::vector<T>& vec)
: d_begin(&*vec.begin()),
  d_end(&*vec.end())
{
}

template<class T>
ArrayRef<T>::ArrayRef(T* begin, T* end)
: d_begin(begin),
  d_end(end)
{
}

template<class T>
T*
ArrayRef<T>::begin()
{
    return d_begin;
}

template<class T>
const T*
ArrayRef<T>::begin() const
{
    return d_begin;
}

template<class T>
T*
ArrayRef<T>::end()
{
    return d_end;
}

template<class T>
const T*
ArrayRef<T>::end() const
{
    return d_end;
}

template<class T>
typename ArrayRef<T>::reverse_iterator
ArrayRef<T>::rbegin()
{
    return std::reverse_iterator<T*>(d_end);
}

template<class T>
typename ArrayRef<T>::const_reverse_iterator
ArrayRef<T>::rbegin() const
{
    return std::reverse_iterator<const T*>(d_end);
}

template<class T>
typename ArrayRef<T>::reverse_iterator
ArrayRef<T>::rend()
{
    return std::reverse_iterator<T*>(d_begin);
}

template<class T>
typename ArrayRef<T>::const_reverse_iterator
ArrayRef<T>::rend() const
{
    return std::reverse_iterator<const T*>(d_begin);
}

template<class T>
T&
ArrayRef<T>::front()
{
    return *d_begin;
}

template<class T>
const T&
ArrayRef<T>::front() const
{
    return *d_begin;
}

template<class T>
T&
ArrayRef<T>::back()
{
    return *(d_end - 1);
}

template<class T>
const T&
ArrayRef<T>::back() const
{
    return *(d_end - 1);
}

template<class T>
size_t
ArrayRef<T>::size() const
{
    return d_end - d_begin;
}

template<class T>
bool
ArrayRef<T>::empty() const
{
    return d_end == d_begin;
}

template<class T>
T&
ArrayRef<T>::operator [] (size_t index)
{
    return d_begin[index];
}

template<class T>
const T&
ArrayRef<T>::operator [] (size_t index) const
{
    return d_begin[index];
}

template<class T>
T&
ArrayRef<T>::at(size_t index)
{
    T* ptr = d_begin + index;
    if (ptr < d_end) {
        return *ptr;
    }
    else {
        throw std::out_of_range("ArrayRef<...>::at(): index out of range");
    }
}

template<class T>
const T&
ArrayRef<T>::at(size_t index) const
{
    const T* ptr = d_begin + index;
    if (ptr < d_end) {
        return *ptr;
    }
    else {
        throw std::out_of_range("ArrayRef<...>::at(): index out of range");
    }
}

#endif /* INCLUDED_ARRAYREF */
