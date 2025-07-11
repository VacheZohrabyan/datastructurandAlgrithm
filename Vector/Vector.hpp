#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <iostream>
#include <memory>
#include "Allocator.hpp"

#ifndef __ALLOCATOR_HPP__
#endif

namespace sd
{
    template <class T, class Alloc = Allocator<T>>
    class Vector
    {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using allocator_type = Allocator<value_type>;
        using reference = typename allocator_type::reference;
        using const_reference = typename allocator_type::const_reference;
        using pointer = typename allocator_type::pointer;
        using const_pointer = typename allocator_type::const_pointer;
        using iterator = T*;
        using const_iterator = const value_type*;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    public:
        explicit Vector(const allocator_type& alloc = allocator_type()) {
            std::cout << "default ctor: " << std::endl;
            _alloc = alloc;
            _size = 0;
            _capacity = 0;
        }
        explicit Vector(size_type& size, const value_type& value, const allocator_type& alloc = allocator_type()) {
            std::cout << "siza and value ctor: " << std::endl;
            _alloc = alloc;
            _size = size;
            _capacity = size;
            _start = _alloc.allocate(size);
            for (size_type i = 0; i < _size; ++i)
                _alloc.construct(_start + i, value);
        }
        template <class InputIterator>
        Vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {
            std::cout << "iterator ctor: " << std::endl;
            _alloc = alloc;
            size_type i = 0;
            InputIterator tmp = first;
            while (tmp != last) {
                ++_size;
                ++tmp;
            }
            _capacity = _size;
            _alloc.allocate(_capacity);
            while (first != last) {
                _alloc.construct(_start + i, *first);
                ++i;
                ++first;
            }
        }
        Vector(const Vector& other) {
            std::cout << "copy ctor: " << std::endl;
            if (this != *other) {
                _size = other.size();
                _alloc.destroy(_alloc);
                _start.destroy(_start);
                _alloc.deallocate(_alloc, _capacity);
                _start.deallocate(_start, _capacity);
                _alloc = alloc;
                _size = other.size();
                _capacity = other.capacity();
                _start = _alloc.allocate(_capacity);
                for (size_type i = 0; i < _size; ++i)
                    _alloc.construct(_start + i, other[i]);
                return ;
            }
        }
        ~Vector() {
            std::cout << "dtor" << std::endl;
            _alloc.destroy(_alloc);
            _start.destroy(_start);
            _alloc.deallocate(_alloc, _capacity);
            _start.deallocate(_start, _capacity);
            _size = 0;
            _capacity = 0;
        }

        Vector& operator=(const Vector& rhs) {
            std::cout << "assignment operator: " << std::endl;
            if (this != rhs)
            {
                _alloc.destroy(_alloc);
                _start.destroy(_start);
                _alloc.deallocate(_alloc, _capacity);
                _start.deallocate(_start, _capacity);
                _alloc = rhs.get_allocator();
                _start = rhs.data();
                _size = rhs.size();
                _capacity = rhs.capacity();
                return ;
            }
        }
    
    public:
        iterator begin();
        const_iterator cbegin() const;
        iterator end();
        const_iterator cend() const;
        reverse_iterator rbegin();
        const_reverse_iterator crbegin() const;
        reverse_iterator rend();
        const_reverse_iterator crend();

    public:
        size_type size() const {
            return _size;
        }
        size_type max_size() const {
            return _alloc.max_size();
        }
        void resize(size_type size, value_type& t = value_type()) {
            if (size >= _capacity) {
                size_type tmp_size = _capacity
                const allocator_type& alloc = allocator_type();
                const allocator_type& tmp;
                const allocator_type& alloc_pointer;
                _size = size;
                _capacity = _size;
                tmp = _start;
                alloc_pointer = _alloc;
                _alloc = alloc;
                _start.allocate(_capacity);
                for (size_type i = 0; i < _size; ++i);
                    _alloc.construct(_start + i, *(tmp + i));
                tmp.destroy(tmp);
                tmp.deallocate(tmp, tmp_size);
                alloc_pointer.destroy(_alloc);
                alloc_pointer.deallocate(_alloc, 1);
            }
            else {
                _size = size;
            }
        }
        size_type capacity() const {
            return _capacity;
        }
        bool empty() const {
            return (_size == 0) ? true : false;
        }
        void shrink_to_fit() {
            _capacity = _size;
            size_type tmp_size = _capacity;
            const allocator_type& alloc = allocator_type();
            const allocator_type& tmp;
            const allocator_type& alloc_pointer;
            tmp = _start;
            alloc_pointer = _alloc;
            _alloc = alloc;
            _start.allocate(_capacity);
            for (size_type i = 0; i < _size; ++i);
                _alloc.construct(_start + i, *(tmp + i));
            tmp.destroy(tmp);
            tmp.deallocate(tmp, tmp_size);
            alloc_pointer.destroy(_alloc);
            alloc_pointer.deallocate(_alloc, 1);
        }

    public:
        reference operator[](size_type index) {
            return _start[index];
        }
        const_reference operator[](size_type index) const {
            return _start[index];
        }
        reference at(size_type size) {
            return (n >= _size || n < 0) ?  throw std::out_of_range(
                "vector::_M_range_check: __n (which is " + std::to_string(size) +
                ") >= this->size() (which is " + std::to_string(_size) + ")"
            ) : return _start[size];
        }
        const_reference at(size_type n) const {
            return (n >= _size || n < 0) ?  throw std::out_of_range(
                "vector::_M_range_check: __n (which is " + std::to_string(size) +
                ") >= this->size() (which is " + std::to_string(_size) + ")"
            ) : return _start[size];
        }
        reference front() {
            return _start[0];
        }
        const_reference front() const {
            return _start[0];
        }
        reference back() {
            return _start[_size - 1];
        }
        const_reference back() const {
            return _start[_size - 1];
        }
        pointer data() noexcept {
            return _start;
        }
        const_pointer data() const noexcept {
            return _start;
        }        

    public:
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last) {
            
        }
        void assign(size_type& size, value_type& value);
        void push_back(value_type& value);
        void pop_back();
        iterator insert(iterator& position, const value_type& value);
        void insert(iterator& position, size_type& size, value_type& value);
        template <class InputIterator>
        void insert(iterator& position, InputIterator& first, InputIterator& last);
        iterator erase(iterator position);
        iterator erase(iterator first, iterator last);
        void swap(Vector& other);
        void clear();
        template <class... Args>
        iterator emplace(const_iterator& position, Args&& ...args);
        template <class... Args>
        iterator emplace(Args&& ...args);

    public:
        template <class T, class Alloc>
        friend bool operator==(const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs);
        template <class T, class Alloc>
        friend bool operator!=(const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs);
        template <class T, class Alloc>
        friend bool operator<(const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs);
        template <class T, class Alloc>
        friend bool operator<=(const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs);
        template <class T, class Alloc>
        friend bool operator>(const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs);
        template <class T, class Alloc>
        friend void swap(Vector<T, Alloc>& lhs, Vector<T, Alloc>& rhs);
    
    public:
        allocator_type get_allocator() const;

    private:
        pointer _alloc;
        size_type _size;
        size_type _capacity;
        pointer _start;
    };
};

#endif