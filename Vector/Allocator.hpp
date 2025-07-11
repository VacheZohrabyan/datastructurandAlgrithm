#ifndef __ALLOCATOR_HPP__
#define __ALLOCATOR_HPP__

#include <iostream>
#include <new>
#include <limits>

namespace sd
{
    template <class T>
    class Allocator
    {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using pointer = T*;
        using const_pointer = const value_type*;
        using reference = value_type&;
        using const_reference = const value_type&;
        using difference_type = std::ptrdiff_t;

    public:
        Allocator() throw() {};
        Allocator(const Allocator& ) throw() {}
        template <class U>
        Allocator(const Allocator<U>&) throw() {}
        ~Allocator() throw() {}

    public:
        template <class U>
        class rebind
        {
        public:
            using other = Allocator<U>;
        };
    
    public:
        pointer address(reference value) const {
            return &value;
        }
        const_pointer address(const_reference value) const {
            return &value;
        }

    public:
        size_type max_size() const {
            return std::numeric_limits<size_type>::max() / sizeof(value_type);
        }
        pointer allocate(size_type num, const void* hint = 0) throw() {
            return (pointer)(::operator new(num * sizeof(value_type)));
        }
        void construct(pointer ptr, const value_type& value) {
            new ((void*)ptr) value_type(value);
        }
        void destroy(pointer p) {
            ((value_type*)p)->~value_type();
        }
        void deallocate(pointer p, size_type num) {
            ::operator delete ((void*)p);
        }
    };

    template<class T1, class T2>
    bool operator== (const Allocator<T1> alloc1, const Allocator<T2> alloc2) throw() {
        return true;
    }
    
    template<class T1, class T2>
    bool operator!= (const Allocator<T1> alloc1, const Allocator<T2> alloc2) throw() {
        return false;
    }
};

#endif