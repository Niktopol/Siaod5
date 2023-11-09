#ifndef BINF_WORKER
#define BINF_WORKER
#include <fstream>
#include <string>
#include "bin_tree.h"
#include "structures.h"
class binf_worker{
    std::fstream file;
    int size;
    bin_tree* binary_tree;
public:
    binf_worker();
    void gen_file(unsigned int size);
    int get_size();
    void print_tree();
    void write_to_file(patient_info&);
    void remove_from_file(unsigned int);
    std::string find_in_file(unsigned int);
    std::string find_by_bin_tree(int);
    std::string find_by_b_tree(int);
    std::string find_by_hash_table(int);
    ~binf_worker();
};
#endif