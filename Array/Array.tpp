#include "Array.hpp"

template<typename T, std::size_t N>
st::Array<T, N>::Array() : _size{N}
{
    _arr = new T[_size];
}

template<typename T, std::size_t N>
st::Array<T,N>::Array(const Array& other)
{
    if (this != *other)
        this = other;
}

template<typename T, std::size_t N>
st::Array<T,N>::Array(const Array&& other)
{
    if (this != *other)
    {
        if (!empty())
        {
            for (size_type i = 0; i < _size; ++i)
            {
                T tmp = _arr[i];
                _arr[i] = std::move(other[i]);
                other[i] = tmp;
            }
        }
    }
}

template<typename T, std::size_t N>
st::Array<T, N>::Array(std::initializer_list<T> elem) : _arr(new T[N])
{
    size_type i = 0;
    _size = N;
    for (const T& el: elem)
    {
        if (i >= N) return;
        _arr[i++] = el;
    }
    while (i < N)
        _arr[i++] = 0;
}

template<typename T, std::size_t N>
st::Array<T,N>::~Array()
{
    delete[] _arr;
}

template<typename T, std::size_t N>
st::Array<T, N>& st::Array<T, N>::operator=(const Array& other)
{
    if (this != *other)
    {
        if (!empty())
        {
            for (size_type i = 0; i < _size; ++i)
            {
                T tmp = _arr[i];
                _arr[i] = other[i];
                other[i] = tmp;
            }
        }
    }
    return *this;
}

template<typename T, std::size_t N>
T st::Array<T, N>::operator[](const int index)
{
    return _arr[index];
}

template<typename T, std::size_t N>
typename st::Array<T, N>::reference st::Array<T, N>::at(size_type index)
{
    if (index >= _size)
        throw std::out_of_range(
            "array::at: __n (which is " + std::to_string(index) +
            ") >= _Nm (which is " + std::to_string(_size) + ")"
        );
    return (_arr[index]);
}

template<typename T, std::size_t N>
typename st::Array<T, N>::const_reference st::Array<T, N>::at(size_type index) const
{
    if (index >= _size)
        throw std::out_of_range(
            "array::at: __n (which is " + std::to_string(index) +
            ") >= _Nm (which is " + std::to_string(_size) + ")"
        );
    return (_arr[index]);
}

template<typename T, std::size_t N>
typename st::Array<T, N>::reference st::Array<T, N>::front()
{
    if (empty())
        return _arr[0];
    return _arr[0];
}

template<typename T, std::size_t N>
typename st::Array<T, N>::const_reference st::Array<T, N>::front() const
{
    if (empty())
        return _arr[0];
    return _arr[0];
}

template<typename T, std::size_t N>
typename st::Array<T, N>::reference st::Array<T, N>::back()
{
    if (empty())
        return _arr[0];
    return _arr[_size - 1];
}

template<typename T, std::size_t N>
typename st::Array<T, N>::const_reference st::Array<T, N>::back() const
{
    if (empty())
        return _arr[0];
    return _arr[_size - 1];
}

template<typename T, std::size_t N>
typename st::Array<T, N>::pointer st::Array<T, N>::data() noexcept
{
    if (_arr == NULL && empty())
        return NULL;
    return _arr;
}

template<typename T, std::size_t N>
typename st::Array<T, N>::const_pointer st::Array<T, N>::data() const noexcept
{
    if (_arr == NULL && empty())
        return NULL;
    return _arr;
}

template<typename T, std::size_t N>
constexpr bool st::Array<T, N>::empty() const noexcept
{
    if (_arr == NULL || _size == 0)
        return true;
    return false;
}

template<typename T, std::size_t N>
constexpr typename st::Array<T, N>::size_type st::Array<T, N>::size() const noexcept
{
    return N;
}

template<typename T, std::size_t N>
constexpr typename st::Array<T, N>::size_type st::Array<T, N>::max_size() const noexcept
{
    return _size;
}

template<typename T, std::size_t N>
void st::Array<T, N>::fill(const reference value)
{
    if (_size == 0)
        return ;
    for (size_type i = 0; i < _size; ++i)
        _arr[i] = value;
}

template<typename T, std::size_t N>
void st::Array<T, N>::swap(Array& other) noexcept
{
    if (_arr == other.data() && _size == other.size())
        return ;
    for (size_type i = 0; i < _size; ++i)
    {
        T tmp = _arr[i];
        _arr[i] = other.data()[i];
        other.data()[i] = tmp;
    }
}