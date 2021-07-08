//
// Created by WU on 2021/7/8.
//

#ifndef MYSTL_TYPE_TRAITS_H
#define MYSTL_TYPE_TRAITS_H
namespace wfs {
    struct __true_type {};
    struct __false_type {};

    template <class type>
    struct __type_traits{
        typedef __false_type has_trivial_default_constructor;
        typedef __false_type has_trivial_copy_constructor;
        typedef __false_type has_trivial_assignment_operator;
        typedef __false_type has_trivial_destructor;
        typedef __false_type has_POD_type;
    };
    //上面这个泛化版本可以把所有stl 和 自建类型认为是没有trivial的
    //但是下面的特化版本则是把所有内置类型都置为true

    template <>
    struct __type_traits<char>{
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type has_POD_type;
    };

    template <>
    struct __type_traits<short>{
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type has_POD_type;
    };

    template <>
    struct __type_traits<unsigned short >{
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type has_POD_type;
    };

    template <>
    struct __type_traits<int >{
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type has_POD_type;
    };

    template <>
    struct __type_traits<unsigned int >{
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type has_POD_type;
    };

    template <>
    struct __type_traits<long >{
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type has_POD_type;
    };

    template <>
    struct __type_traits<unsigned long >{
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type has_POD_type;
    };

    template <>
    struct __type_traits<float >{
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type has_POD_type;
    };

    template <>
    struct __type_traits<double>{
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type has_POD_type;
    };

    //还有一些没写，太多了

}
#endif //MYSTL_TYPE_TRAITS_H
