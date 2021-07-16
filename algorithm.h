//
// Created by WU on 2021/7/15.
//

#ifndef MYSTL_ALGORITHM_H
#define MYSTL_ALGORITHM_H

#include "traits/iterator_traits.h"
namespace wfs {
    template<class RandomAccessIterator, class Distance, class T>
    void __push_heap(RandomAccessIterator first, Distance top, Distance holeIndex, T value){
        while (holeIndex > top) {
            Distance parent = (holeIndex - 1) / 2;
            if (*(first + parent) < value) {
                *(first + holeIndex) = *(first + parent);
                holeIndex = parent;
            } else {
                break;
            }
        }
        *(first + holeIndex) = value;
    }
    //调整一颗子树
    template<class RandomAccessIterator, class Distance, class T>
    void __adjust_heap(RandomAccessIterator first, Distance holeIndex, Distance len, T value) {
        Distance top = holeIndex;
        Distance left = 2 * holeIndex + 1, right = 2 * holeIndex + 2;
        while (right <= len - 1) {
            T value_left = *(first + left), value_right = *(first + right);
            if (value_left < value_right) {
                *(first + holeIndex) = value_right;
                holeIndex = right;
            } else {
                *(first + holeIndex) = value_left;
                holeIndex = left;
            }
            left = 2 * holeIndex + 1, right = 2 * holeIndex + 2;
        }
        if (right == len) {
            T value_left = *(first + left);
            *(first + holeIndex) = value_left;
            holeIndex = left;
        }

        __push_heap(first, top, holeIndex, value);
    }


    template<class RandomAccessIterator, class T, class Distance>
    void __make_heap(RandomAccessIterator first, RandomAccessIterator last, T, Distance) {
        Distance len = (last - first);
        Distance holeIndex = (len - 2) / 2;
        while (1) {
            __adjust_heap(first, holeIndex, len, T(*(first + holeIndex)));
            if (holeIndex == 0) return;
            --holeIndex;
        }
    }
    template<class RandomAccessIterator, class T, class Distance>
    void __pop_heap(RandomAccessIterator first, RandomAccessIterator last,  T, Distance) {
        T value = *(last - 1);
        *(last - 1) = *first;
        __adjust_heap(first,0,(last- first), value);
    }

    template<class RandomAccessIterator>
    void make_heap(RandomAccessIterator first,  RandomAccessIterator last) {
        __make_heap(first, last, typename iterator_traits<RandomAccessIterator>::value_type(),typename iterator_traits<RandomAccessIterator>::difference_type());
    }

    template<class RandomAccessIterator>
    void push_heap(RandomAccessIterator first, RandomAccessIterator last) {
        __push_heap(first, 0, (last - first - 1), *(last-1));
    }

    template<class RandomAccessIterator>
    void pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
        __pop_heap(first, last, typename iterator_traits<RandomAccessIterator>::value_type(),typename iterator_traits<RandomAccessIterator>::difference_type());
    }


}

#endif //MYSTL_ALGORITHM_H
