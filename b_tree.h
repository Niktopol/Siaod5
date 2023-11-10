#ifndef B_TREE
#define B_TREE
#include "structures.h"
#include <iostream>
#include <cmath>
#include <queue>

class b_tree{
    struct tree_item{
        int val_count;
        bool has_children;
        patient** values;
        tree_item** children;
        int param;
        bool add_val(int, unsigned int);
        void add_children(tree_item*, tree_item*, tree_item*);
        int find_item(int);
        void print_self(std::string,std::string);
        tree_item(int);
        ~tree_item();
    };
    tree_item* root;
    int records;
    int key_size;
    int height;
    int param;
    tree_item* get_left_part(tree_item*);
    tree_item* get_right_part(tree_item*);
    public:
    void add_item(int, unsigned int);
    int find_item(int);
    void remove_item(int);
    void print_tree();
    b_tree(int);
    ~b_tree();
};
#endif