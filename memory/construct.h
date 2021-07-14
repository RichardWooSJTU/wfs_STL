//
// Created by WU on 2021/7/8.
//

#ifndef MYSTL_CONSTRUCT_H
#define MYSTL_CONSTRUCT_H
#include <new>
#include "../traits/iterator_traits.h"
#include "../traits/type_traits.h"
namespace wfs {
    template<class T1, class T2>
    inline void construct(T1* p, const T2& v) {
        new (p) T1(v);
    }

    template<class T>
    inline void destroy(T* p) {
        p->~T();
    }

    template<class ForwardIterator>
    inline void __destroy_aux(ForwardIterator first, ForwardIterator last, __true_type){}//类型为true_type的重载

    template<class ForwardIterator>
    inline void __destroy_aux(ForwardIterator first, ForwardIterator last, __false_type) {
        //类型为false_type的重载，一般就是stl类或者自建类
        while (first != last) {
            destroy(&(*first));
            ++first;
        }
    }
    template<class ForwardIterator, class T>
    inline void __destroy(ForwardIterator first, ForwardIterator last, T) {
        typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
        __destroy_aux(first, last, trivial_destructor());
    }

    //destroy 常用版本
    template<class ForwardIterator>
    inline void destroy(ForwardIterator first,  ForwardIterator last) {
        //这里需要区分一下trivial 析构函数的 因为内置类型是没有析构函数的，调用会出错
        //所以这里还是需要traits来判断是不是trivial
        __destroy(first, last, typename iterator_traits<ForwardIterator>::value_type());
    }
    template<class T>
    inline void copy(T* old_start, T* old_finish ,T* new_start) {
        for (; old_start < old_finish; ++old_start) {
            construct(new_start, *old_start);
            ++old_start;
        }
    }
}

#endif //MYSTL_CONSTRUCT_H
