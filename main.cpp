#include <iostream>
#include "binf_worker.h"
#include "b_tree.h"
#include <string>
#include <vector>
#include <chrono>

int main(){
    srand(time(nullptr));
    binf_worker worker;
    //auto begin = std::chrono::high_resolution_clock::now();
    //std::cout << "Table created in: " << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - begin).count() << " ns\n";
    worker.gen_file(1000000);
    int a;
    std::cin >> a;
    std::cout<< worker.find_by_bin_tree(a) <<std::endl;
    std::cout<< worker.find_by_b_tree(a) <<std::endl;
    std::cout<< worker.find_by_hash_table(a) <<std::endl;
    worker.remove_from_file(a);
    std::cout<< worker.find_by_bin_tree(a) <<std::endl;
    std::cout<< worker.find_by_b_tree(a) <<std::endl;
    std::cout<< worker.find_by_hash_table(a) <<std::endl;
    std::cin >> a;
    std::cout<< worker.find_by_bin_tree(a) <<std::endl;
    std::cout<< worker.find_by_b_tree(a) <<std::endl;
    std::cout<< worker.find_by_hash_table(a) <<std::endl;
    std::cin >> a;
    std::cout<< worker.find_by_bin_tree(a) <<std::endl;
    std::cout<< worker.find_by_b_tree(a) <<std::endl;
    std::cout<< worker.find_by_hash_table(a) <<std::endl;
    worker.remove_from_file(a);
    std::cout<< worker.find_by_bin_tree(a) <<std::endl;
    std::cout<< worker.find_by_b_tree(a) <<std::endl;
    std::cout<< worker.find_by_hash_table(a) <<std::endl;
    
/*
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.erase(vec.begin()+1);
    for(int i = 0; i < 3; i++){
        std::cout << vec.at(i) << std::endl;
    //}*/
    //bin_tree tree
    /*
    b_tree tree(2);
    //int a[30];
    for (int i = 0; i < 10000; i++){
        tree.add_item(rand(),i);
        //std::cout << "------" << std::endl;
    }
    
    tree.print_tree();
    int key = 0;
    std::cin  >> key;
    tree.remove_item(key);
    tree.print_tree();*/
    //tree.add_item(key, 9999);
    //tree.print_tree();

/*

    int a[30];
    for (int i = 0; i < 30; i++){
        a[i] = rand()%1000;
        //std::cout << "------" << std::endl;
    }
    b_tree* tr;
    for(int i = 0; i < 30; i++){
        tr = new b_tree(2);
        for(int j = 0; j < 30; j++){
            tr->add_item(a[j], j);
        }
        tr->remove_item(a[i]);
        tr->print_tree();
        std::cout << "------" << std::endl;
        delete tr;
    }*/
    /*
    tree.print_tree();
    int key = 0;
    std::cin  >> key;
    tree.remove_item(key);
    tree.print_tree();
    std::cout << tree.find_item(key) << std::endl;*/

    return 0;
}