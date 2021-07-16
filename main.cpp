#include <iostream>
#include "my_allocator.h"
#include "container/my_vector.h"
#include "container/my_deque.h"
#include "algorithm.h"
int main() {
    // vector
//    wfs::vector<int> vec;
//    int prev = 1, cur = 1;
//    for (int i = 2; i < 20; ++i) {
//        int tmp = cur;
//        cur = tmp + prev;
//        prev = tmp;
//        vec.push_back(cur);
//    }
//    for (auto i : vec) std::cout << i << std::endl;
    //deque

//    wfs::deque<int> deq(20, 9);
//    auto iter = deq.begin();
//    while (iter != deq.end()) {
//        std::cout << *iter << std::endl;
//        ++iter;
//    }
//    return 0;
//    int x = 1;
//    int *p = &x;
//    std::cout << *(p+2) << std:: endl;

    wfs::vector<int> s(6, 1);
    for (int i = 1; i < 7; ++i) {
        s[i-1] = i;
    }

    wfs::make_heap(s.begin(), s.end());

    for (int i = 0; i < 10; ++i) {
        std::cout << s[i] << std::endl;
    }
    return 0;


}
