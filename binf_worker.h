#ifndef BINF_WORKER
#define BINF_WORKER
#include <fstream>
#include <iostream>
#include <string>
#include "bin_tree.h"
#include "b_tree.h"
#include "hash_table.h"
#include "structures.h"
class binf_worker{
    std::fstream file;
    int size;
    bin_tree* binary_tree;
    b_tree* btree;
    hash_table* table;
    std::string find_in_file(int);
public:
    binf_worker();
    void gen_file(unsigned int size);
    int get_size();
    void print_binary_tree();
    void print_b_tree();
    void print_hash_table();
    void write_to_file(patient_info&);
    void remove_from_file(int);
    std::string find_by_bin_tree(int);
    std::string find_by_b_tree(int);
    std::string find_by_hash_table(int);
    ~binf_worker();
};
#endif