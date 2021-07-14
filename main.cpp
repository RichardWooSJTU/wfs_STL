#include <iostream>
#include "my_allocator.h"
#include "container/my_vector.h"
#include "container/my_deque.h"

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

    wfs::deque<int> deq(20, 9);
    auto iter = deq.begin();
    while (iter != deq.end()) {
        std::cout << *iter << std::endl;
        ++iter;
    }
    return 0;
}
