#include <iostream>
#include "binf_worker.h"
#include "b_tree.h"
#include <string>

int main(){
    srand(time(nullptr));

    //bin_tree tree;
    b_tree tree(2);
    
    for (int i = 0; i < 85; i++){
        int rnd = rand()%1000;
        tree.add_item(rnd, i);
        //tree.print_tree();
        //std::cout << "------" << std::endl;
    }
    tree.print_tree();
    int key = 0;
    std::cin  >> key;
    tree.remove_item(key);
    tree.print_tree();
    //std::cout << tree.find_item(key) << std::endl;
    return 0;
}