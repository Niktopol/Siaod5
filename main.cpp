#include <iostream>
#include "binf_worker.h"
#include "b_tree.h"
#include <string>

int main(){
    //srand(time(nullptr));

    //bin_tree tree
    b_tree tree(2);
    //int a[30];
    for (int i = 0; i < 30; i++){
        int rnd = rand()%1000;
        //a[i] = rnd;
        tree.add_item(rnd, i);
        tree.print_tree();
        //std::cout << "------" << std::endl;
    }
    /*
    for(int i = 0; i < 30; i++){
        b_tree* tr = new b_tree(2);
        for(int j = 0; j < 30; j++){
            tr->add_item(a[j], j);
        }
        tr->remove_item(a[i]);
        delete tr;
    }*/
    tree.print_tree();
    int key = 0;
    std::cin  >> key;
    tree.remove_item(key);
    tree.print_tree();
    std::cout << tree.find_item(key) << std::endl;
    return 0;
}