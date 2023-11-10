#ifndef BIN_TREE
#define BIN_TREE
#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include "structures.h"

class bin_tree{
    struct tree_item{
        tree_item* left;
        tree_item* right;
        patient* value;
        void decr_ind(unsigned int);
        tree_item(patient*);
        ~tree_item();
    };
    int records;
    int key_size;
    int height;
    tree_item* root;
    public:
    void add_item(int, unsigned int);
    int find_item(int);
    void remove_item(int);
    void print_tree();
    bin_tree();
    ~bin_tree();
};
#endif