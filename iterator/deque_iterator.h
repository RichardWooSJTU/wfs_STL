//
// Created by WU on 2021/7/14.
//

#ifndef MYSTL_DEQUE_ITERATOR_H
#define MYSTL_DEQUE_ITERATOR_H

#include <bits/stl_iterator_base_types.h>
#include "../my_allocator.h"

namespace wfs {
    template<class T, class Alloc = allocator<T>>
    class __deque_iterator {
    private:
        static const size_t buf_size = 512;
    public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef size_t size_type;
        typedef T *iterator;
        typedef ptrdiff_t difference_type;

        typedef __deque_iterator<T> self;
        pointer first;
        pointer last;
        pointer cur;
        pointer* node;

        inline size_t buffer_size() {
            return buf_size;
        }



    public:
        void set_node(pointer* new_node) {
            node = new_node;
            first = *new_node;
            last = *new_node + buffer_size();
        }
        reference operator*() const {return *cur;}
        pointer operator->() const {return &(operator*());}
        difference_type operator-(const self& r) const {
            difference_type res = difference_type(buffer_size()) * (node-r.node-1) +
                    (cur - first) + (r.last - r.cur);//这里没有分r是不是也在当前缓冲区，是因为node-r.node-1会等于-1把后面多算的再减掉
            return res;
        }
        self& operator++() {//这里没有const 是因为 常值自加是不是不太正常
            ++cur;
            if (cur == last) {
                node++;
                /*
                if (node == map+map_size()) {
                    //重新分配 以及重新赋值 我没想通这里 是不打算进行错误处理么 一直加？
                    // 实验之后确实是，iter会一直加，只要不对其进行取值，这个值就不会抛出错误


                }
                 */
                first = *node;
                last = first + difference_type(buffer_size());
                cur = first;
            }
            return *this;
        }
        self& operator++(int) {
            self t = *this;
            operator++();
            return *t;
        }

        self& operator--() {
            if (cur == first) {
                node--;
                first = *node;
                last = first + difference_type(buffer_size());
                cur = last;
            }
            --cur;
        }

        self& operator--(int) {
            self t = *this;
            operator--();
            return *t;
        }

        self& operator+=(difference_type n) {
            for (int i = 0; i < n; ++i) operator++();//极低的效率
            return *this;
        }
        self operator+(difference_type n) const  {
            self t = *this;
            return (t+=n);
        }
        self& operator-=(difference_type n) {
            for (int i = 0; i < n; ++i) operator--();
            return *this;
        }
        self operator-(difference_type n) const {
            self t = *this;
            return (t-=n);
        }

        bool operator==(const self& r) const {return cur == r.cur;}
        bool operator!=(const self& r) const {return !(cur == r.cur);}
        bool operator<(const self& r) const {
            return (node == r.node) ? (cur < r.cur) : (node < r.node);
        }



    };
}

#endif //MYSTL_DEQUE_ITERATOR_H
