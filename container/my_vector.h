//
// Created by WU on 2021/7/8.
//

#ifndef MYSTL_MY_VECTOR_H
#define MYSTL_MY_VECTOR_H

#include "../my_allocator.h"
#include "../memory/uninitialized.h"
#include <memory>
#include <iostream>
namespace wfs {
    template<class T, class Alloc = allocator<T>>
    class vector {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef size_t size_type;
        typedef T *iterator;
        typedef ptrdiff_t difference_type;
    protected:
        iterator start;
        iterator finish;
        iterator end_of_storage;

        Alloc data_allocator;

        iterator allocate_and_fill(size_type n, const value_type& x) {
            //初始化空间并填满，走到这里发现allocator还不够，这里需要的不是指针而是迭代器 但是vector的迭代器确实就是指针，emmm 先这么用吧， 看看其他容器
            iterator result = data_allocator.allocate(n);
            uninitialized_fill_n(result, n, x);
            return result;
        }

        void fill_initialize(size_type n, const value_type& x) {
            start = allocate_and_fill(n, x);
            finish = start + n;
            end_of_storage = start + n;
        }

        void insert_aux(iterator pos, const value_type& x) {
            if (finish != end_of_storage) {
                uninitialized_copy(pos, finish, pos+1);
                finish++;
                *pos = x;
            } else {
                size_type old_size = size();
                size_type new_capacity;
                size_type dist = pos - start;
                if (old_size == 0) new_capacity = 1;
                else new_capacity = 2 * old_size;
                iterator new_start = allocate_and_fill(new_capacity, 0);
                uninitialized_copy(start, finish, new_start);
                destroy(start, finish);
                data_allocator.deallocate(start, old_size);
                start = new_start;
                finish = new_start + old_size;
                end_of_storage = new_start + new_capacity;
                insert_aux(start+dist, x);
            }
        }

    public:
        vector():start(0), finish(0), end_of_storage(0){}
        vector(size_type n, const value_type& v) {
            fill_initialize(n, v);
        }

        explicit vector(size_type n){
            fill_initialize(n, T());
        }

        ~vector() {
            destroy(start, finish);
            data_allocator.deallocate(start, end_of_storage - start);
        }

        size_type size() {return size_type(finish - start);}
        iterator begin() {return start;}
        iterator end() {return finish;}

        void push_back(value_type& x) {
            if (finish != end_of_storage) {
                construct(finish, x);
                ++finish;
            }
            else {
                insert_aux(finish, x);
            }
        }
    };
}

#endif //MYSTL_MY_VECTOR_H
