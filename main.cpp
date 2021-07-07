#include <iostream>
#include "my_allocator.h"
#include <vector>

int main() {
    std::vector<int,wfs::allocator<int>> vec;
    int prev = 1, cur = 1;
    for (int i = 2; i < 20; ++i) {
        int tmp = cur;
        cur = tmp + prev;
        prev = tmp;
        vec.push_back(cur);
    }
    for (auto i : vec) std::cout << i << std::endl;
    return 0;
}
