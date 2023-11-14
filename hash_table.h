#ifndef HASH_TABLE
#define HASH_TABLE
#include <forward_list>
#include "structures.h"
#include <iostream>
class hash_table{
    int size;
    int records;
    std::forward_list<patient> *table;
    void re_hash();
public:
    void push_key(int, unsigned int);
    int find(int);
    int remove(int);
    void print_table();
    hash_table();
    ~hash_table();
};
#endif