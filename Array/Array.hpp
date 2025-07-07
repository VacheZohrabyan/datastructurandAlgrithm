#pragma once

#include <iostream>
#include <climits>

namespace st
{
    template<typename T, std::size_t N>
    class Array
    {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
    
    public:
        Array();
        Array(const Array& other);
        Array(const Array&& other);
        Array(std::initializer_list<T> elem);
        ~Array();
        Array& operator=(const Array& other);
        T operator[](const int index);

    public:
        reference at(size_type index); 
        const_reference at(size_type index) const;
        reference front(); 
        const_reference front() const;
        reference back(); 
        const_reference back() const;
        pointer data() noexcept;
        const_pointer data() const noexcept;  
        constexpr bool empty() const noexcept;
        constexpr size_type size() const noexcept;
        constexpr size_type max_size() const noexcept;
        void fill(const reference value);
        void swap(Array& other) noexcept;

    private:
        std::size_t _size;
        T *_arr;
    };

    #include "Array.tpp"
};