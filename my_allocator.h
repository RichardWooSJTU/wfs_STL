//
// Created by WU on 2021/7/7.
//

#ifndef MYSTL_MY_ALLOCATOR_H
#define MYSTL_MY_ALLOCATOR_H
#include <iostream>

namespace wfs {
    template<class T>
    class allocator {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef  size_t size_type;
        typedef  ptrdiff_t difference_type;
        //默认构造 拷贝构造 都用自动生成的

        pointer allocate(size_type n, const void* hint=0) {
            std::cout << "allocate now! " << n << std::endl;
            pointer tmp = (pointer) operator new(n * sizeof(T));
            if (tmp == nullptr) {
                std::cerr << "out of memory" << std::endl;
                return nullptr;
            }
            return tmp;
        }

        void deallocate(pointer p, size_type n) {
            operator delete(p);
        }

        pointer address(reference x) const {
            return (pointer)&x;
        }

        const_pointer address(const_reference x) const {
            return (const_pointer)&x;
        }

        size_type max_size() const {
            return size_type(UINT64_MAX/sizeof(T));
        }

        void construct(pointer p, const T& x) {
            new(p) T(x);
        }

        void destroy(pointer p) {
            p->~T();
        }
    };

}


#endif //MYSTL_MY_ALLOCATOR_H
