//
// Created by WU on 2021/7/14.
//

#ifndef MYSTL_MY_DEQUE_H
#define MYSTL_MY_DEQUE_H
#include "../iterator/deque_iterator.h"
#include "../memory/construct.h"
#include "../memory/uninitialized.h"
namespace wfs {
    template<class T, class Alloc = allocator<T>>
    class deque {
    private:
        static const size_t buf_size = 512;
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef pointer* map_pointer;

        typedef wfs::__deque_iterator<T> iterator;

    protected:
        map_pointer map;
        size_type map_size;
        iterator start;
        iterator finish;

        allocator<value_type> data_allocator;
        allocator<pointer> map_allocator;
        pointer allocate_node() {
            pointer buf = data_allocator.allocate(buf_size);
            return buf;
        }

        void create_map_nodes(size_type n_elements) {
            size_type  n_nodes = n_elements / buf_size + 1;
            map_size = n_nodes + 2;
            map = map_allocator.allocate(map_size);
            map_pointer node_start = map + 1;
            map_pointer node_finish = node_start + n_nodes -1;
            for (map_pointer cur = node_start; cur <= node_finish; ++cur) {
                *cur = allocate_node();
            }
            start.set_node(node_start);
            finish.set_node(node_finish);
            start.cur = start.first;
            finish.cur = finish.first + n_elements % buf_size;
        }

        void fill_initialize(size_type n, const value_type& v) {
            create_map_nodes(n);
            for (map_pointer cur = start.node; cur < finish.node; ++cur) {
                uninitialized_fill(*cur, *cur + buf_size, v);
            }
            uninitialized_fill(finish.first, finish.cur, v);
        }

        void reallocate_map(size_type nodes_to_add, bool is_at_front) {
            size_type old_nodes_nums = finish.node-start.node+1;
            size_type new_nodes_nums = old_nodes_nums + nodes_to_add;
            //应该是不需要扩的时候原地移动，需要扩的时候扩展 为了简单 所有都需要换一个位置
//            if (map_size - new_nodes_nums < 2) {
//                //扩展
//            } else {
//                map_pointer new_node_start = map + (map_size - new_nodes_nums) / 2 + (is_at_front ? nodes_to_add : 0);
//                map_pointer new_node_finish = new_node_start + new_nodes_nums -1;
//            }
            size_type new_map_size = map_size - new_nodes_nums < 2 ?  map_size + std::max<size_type>(map_size, nodes_to_add) + 2
                    : map_size;
            map_pointer new_map = map_allocator.allocate(new_map_size);
            map_pointer new_node_start = new_map + (new_map_size - new_nodes_nums) / 2 + (is_at_front ? nodes_to_add : 0);
            copy(start.node. finish.node+1, new_node_start);
            map_allocator.deallocate(map, map_size);
            map = new_map;
            map_size = new_map_size;
            start.set_node(new_node_start);
            finish.set_node(new_node_start + old_nodes_nums -1);//这个时候只是空间有了但是还没有真实地去扩
        }

        void reserve_map_at_back(size_type nodes_to_add = 1) {
            if (nodes_to_add > map_size - (finish.node-map)) {
                reallocate_map(nodes_to_add, false);
            }
        }

        void reserve_map_at_front(size_type nodes_to_add = 1) {
            if (nodes_to_add > start.node- map) {
                reallocate_map(nodes_to_add, true);
            }
        }
    public:
        iterator begin(){return start;}
        iterator end(){return finish;}
        reference operator[](size_type n) {
            return *(start+n);
        }
        reference front(){return *start;}
        reference back(){return *(finish-1);}
        size_type size(){return finish - start;}
        bool empty() const {return finish == start;}

        //deque() 就用自动生成的默认构造函数即可

        deque(int n):start(), finish(), map(0), map_size(0) {
            fill_initialize(n, value_type());
        }

        deque(int n, value_type& v):start(), finish(), map(0), map_size(0) {
            fill_initialize(n, v);
        }
        deque(int n, value_type v):start(), finish(), map(0), map_size(0) {
            fill_initialize(n, v);
        }

        void push_back(const value_type& v) {
            if (finish.cur != finish.last -1) {
                construct(finish.cur, v);
                ++finish.cur;//finish.cur永远指向最后一个元素的下一个地址
            } else {
                reserve_map_at_back();
                *(finish.node+1) = allocate_node();//初始化的时候只初始化了需要的节点数
                construct(finish.cur, v);
                finish.set_node(finish.node+1);
                finish.cur = finish.first;
            }
        }

        void push_front(const value_type& v) {
            if (start.cur != start.first) {
                construct(start.cur, v);
                --start.cur;//finish.cur永远指向最后一个元素的下一个地址
            } else {
                reserve_map_at_front();
                *(start.node-1) = allocate_node();//初始化的时候只初始化了需要的节点数
                start.set_node(start.node-1);
                start.cur = start.last;
                construct(start.cur, v);
            }
        }

        void pop_back() { //极简版 不考虑释放多余的空间
            --finish;
            destroy(finish.cur);
        }

        void pop_front() {
            destroy(start.cur);
            ++start;
        }

    };
}

#endif //MYSTL_MY_DEQUE_H
