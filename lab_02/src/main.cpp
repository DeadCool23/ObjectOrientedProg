#include <iostream>
#include <algorithm>
#include "list.h"
#include "errors.h"

#include <vector>
int main(void) {
    List<int> h = {8, 6, 4, 2};
    h.debug_print();
    h *= 2;
    std::cout << "Size: " << h.size() << std::endl;
    for (const auto &hh : h)
        std::cout << hh << std::endl;
    return 0;
}