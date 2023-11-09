#include "bin_tree.h"
void bin_tree::tree_item::decr_ind(unsigned int ind){
    if (value->ind > ind){
        value->ind -= 1;
    }
    if(left){
        left->decr_ind(ind);
    }
    if(right){
        right->decr_ind(ind);
    }
};
bin_tree::tree_item::tree_item(patient* value){
    this->left = nullptr;
    this->right = nullptr;
    this->value = value;
};
bin_tree::tree_item::~tree_item(){
    if (value){
        delete value;
    }
    if (left){
        delete left;
    }
    if (right){
        delete right;
    }
}
void bin_tree::add_item(int key, unsigned int index){
    records += 1;
    tree_item** cur = &root;
    int level = 1;
    key_size = (key_size > std::to_string(key).length())? key_size : std::to_string(key).length();
    while(*cur){
        level += 1;
        if((*cur)->value->card_num > key){
            cur = &((*cur)->left);
        }else if((*cur)->value->card_num < key){
            cur = &((*cur)->right);
        }else{
            return;
        }
    }
    height = height < level ? level : height;
    *cur = new tree_item(new patient(key, index));
}
int bin_tree::find_item(int key){
    tree_item* cur = root;
    while(cur){
        if(cur->value->card_num > key){
            cur = cur->left;
        }else if (cur->value->card_num < key){
            cur = cur->right;
        }else{
            return cur->value->ind;
        }
    }
    return -1;
};
void bin_tree::remove_item(int key, tree_item** cur){
    while(*cur){
        if((*cur)->value->card_num > key){
            cur = &((*cur)->left);
        }else if ((*cur)->value->card_num < key){
            cur = &((*cur)->right);
        }else{
            records -= 1;
            if ((*cur)->left && (*cur)->right){
                tree_item** replacement = &((*cur)->right);
                while ((*replacement)->left){
                    replacement = &((*replacement)->left);
                }
                delete (*cur)->value;
                (*cur)->value = new patient((*replacement)->value->card_num, (*replacement)->value->ind);
                remove_item((*cur)->value->card_num, replacement);
            }else if ((*cur)->left){
                tree_item* temp = ((*cur)->left);
                (*cur)->left = nullptr;
                delete *cur;
                *cur = temp;
            }else if ((*cur)->right){
                tree_item* temp = ((*cur)->right);
                (*cur)->right = nullptr;
                delete *cur;
                *cur = temp;
            }else{
                delete *cur;
                *cur = nullptr;
            }
            break;
        }
    }
};
void bin_tree::remove_item(int key){
    if (root){
        int ind = find_item(key);
        if (ind >= 0){
            remove_item(key, &root);
            root->decr_ind(ind);
        }
    }
};
void bin_tree::print_tree(){
    std::queue<tree_item*> queue;
    std::queue<tree_item*> print_queue;
    tree_item* temp;
    std::string gap = "";
    std::string e_gap = "";
    if(root){
        queue.push(root);
        for(int i = 0; i < key_size; i++){
            gap += " ";
            e_gap += "-";
        }
        for(int i = 0; i < height; i++){
            for (int j = 0; j < std::pow(2, i); j++){
                print_queue.push(queue.front());
                queue.pop();
                if(print_queue.back()){
                    queue.push(print_queue.back()->left);
                    queue.push(print_queue.back()->right);
                }else{
                    queue.push(nullptr);
                    queue.push(nullptr);
                }
            }
        }
        for(int level = 1; level <= height; level++){
            for (int gap_left = 0; gap_left <= (height - level - 1); gap_left++){
                for (int pr_gap = 0; pr_gap < std::pow(2,gap_left); pr_gap++){
                    std::cout << gap;
                }
            }
            for (int j = 0; j < std::pow(2, level-1); j++){
                std::string gap_between = "";
                for (int gap_betw = 0; gap_betw <= (height - level); gap_betw++){
                    for (int pr_gap = 0; pr_gap < std::pow(2,gap_betw); pr_gap++){
                        gap_between += gap;
                    }
                }
                if (print_queue.front()){
                    std::cout << print_queue.front()->value->card_num << gap_between;
                }else{
                    std::cout << e_gap << gap_between;
                }
                print_queue.pop();
            }
            std::cout << std::endl;
        }
    }
};

bin_tree::bin_tree(){
    root = nullptr;
    records = 0;
    key_size = 0;
};
bin_tree::~bin_tree(){
    if (root){
        delete root;
    }
}