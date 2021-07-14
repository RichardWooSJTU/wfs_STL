# wfs的STL实现

v0.1

第一遍实现先不考虑效率， 把思想实现完整就算成功

目前进度：

2021.7.7
- allocator 简单的内存分配器

2021.7.8
- memory/construct.h 全局construct 和 destroy
- memory/uninitialized.h  全局的uninitialized_copy, uninitialized_fill
- traits/iterator_traits.h 部分迭代器萃取机
- traits/type_traits.h 部分类型萃取机
- container/my_vector.h vector的简单实现

2021.7.14
- iterator/deque_iterator.h deque的迭代器
- container/deque.h deque的简单实现