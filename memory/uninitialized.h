//
// Created by WU on 2021/7/8.
//

#ifndef MYSTL_UNINITIALIZED_H
#define MYSTL_UNINITIALIZED_H

#include "construct.h"

namespace wfs {
    template <class InputIterator, class ForwardIterator>
    ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result) {
        //标准库中的做法是先萃取first的类型，然后根据是否是内置类型而进行效率上的区分，这里统一使用construct
        ForwardIterator cur = result;
        for (; first != last; ++first, ++cur) {
            construct(&(*cur), *first);
        }
        return cur;
    }
    //TODO: 没想通ForwardIterator 的value_type与InputIterator不同的话应该如何处理，报错？

    template <class ForwardIterator, class T>
    void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x) {
        for (; first != last; ++first) {
            construct(&(*first), x);
        }
    }

    template <class ForwardIterator, class Size, class T>
    void uninitialized_fill_n(ForwardIterator first, Size n, const T& x) {
        for (; n > 0; ++first, --n) {
            construct(&(*first), x);
        }
    }
}

#endif //MYSTL_UNINITIALIZED_H
