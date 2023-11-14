#include "hash_table.h"
void hash_table::re_hash(){
    std::forward_list<patient> *newTable = new std::forward_list<patient>[size * 2];
    for (int i = 0; i < size; i++){
        for (patient& j : table[i]){
            newTable[j.card_num % (size * 2)].push_front(patient(j.card_num, j.ind));
        }
    }
    delete[] table;
    size *= 2;
    table = newTable;
}
void hash_table::push_key(int key, unsigned int ind){
    table[key % size].push_front(patient(key, ind));
    ++records;
    while ((records / size) >= 0.75){
        this->re_hash();
    }
}
int hash_table::find(int key){
    for (patient& i : table[key % size]){
        if (i.card_num == key){
            return i.ind;
        }
    }
    return -1;
}
int hash_table::remove(int key){
    for (patient i : table[key % size]){
        if (i.card_num == key){
            int ind = i.ind;
            table[key % size].remove(i);
            for (int j = 0; j < size; j++){
                for (patient& g : table[j]){
                    if (g.ind > ind){
                        g.ind -= 1;
                    }
                }
            }
            --records;  
            return ind;
        }
    }
    return -1;
}
void hash_table::print_table(){
    for (int i = 0; i < size; i++){
        std::cout << "Row " << i << ": ";
        for (patient& j : table[i]){
            std::cout << j.ind << ' ';
        }
        std::cout << std::endl;
    }
}
hash_table::hash_table(){
    this->size = 8;
    this->records = 0;
    this->table = new std::forward_list<patient>[8];
}
hash_table::~hash_table(){
    delete[] table;
}