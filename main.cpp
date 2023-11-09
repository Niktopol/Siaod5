#include <iostream>
#include "binf_worker.h"
#include "structures.h"

int main(){
    srand(time(nullptr));
    binf_worker worker;

    worker.gen_file(6);
    int key = 0;
    worker.print_tree();
    std::cin >> key;
    std::cout << worker.find_by_bin_tree(key);
    return 0;
}