//
// Created by WU on 2021/7/8.
//

#ifndef MYSTL_ITERATOR_TRAITS_H
#define MYSTL_ITERATOR_TRAITS_H

#include <bits/stl_iterator_base_types.h>

namespace wfs {
    template<class Iterator>
    struct iterator_traits {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator:: difference_type difference_type;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::pointer pointer;
    };

    //偏特化
    template<class T>
    struct iterator_traits<T *> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
    };

    template<class T>
    struct iterator_traits<const T *> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T *pointer;
        typedef const T &reference;
    };

    template <class Iterator>
    inline typename iterator_traits<Iterator>::value_type
    value_type(const Iterator&) {
        return static_cast<typename iterator_traits<Iterator>::value_type>(0);
    }
}
#endif //MYSTL_ITERATOR_TRAITS_H
