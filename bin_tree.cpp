#include "bin_tree.h"
//Метод рекурсивного вывода дерева
void bin_tree::tree_item::print_self(std::string gap_before, std::string self_gap, bool left, bool right){
    if(this->right){
        if ((gap_before.length() > 0) && right){
            this->right->print_self(gap_before.substr(0, gap_before.length()-1)+" "+self_gap.substr(0, self_gap.length()-1) + "|", self_gap, false, true);
        }else{
            this->right->print_self(gap_before+self_gap.substr(0, self_gap.length()-1) + "|", self_gap, false, true);
        }
    }
    if(right){
        std::cout << gap_before.substr(0, gap_before.length()-1) + "┌";
    }else if(left){
        std::cout << gap_before.substr(0, gap_before.length()-1) + "└";
    }
    for (int j = 0; j < self_gap.length() - std::to_string(value->card_num).length(); j++){
        std::cout << " ";
    }
    std::cout << value->card_num << std::endl;
    if(this->left){
        if((gap_before.length() > 0) && left){
            this->left->print_self(gap_before.substr(0, gap_before.length()-1)+" "+self_gap.substr(0, self_gap.length()-1) + "|", self_gap, true, false);
        }else{
            this->left->print_self(gap_before+self_gap.substr(0, self_gap.length()-1) + "|", self_gap, true, false);
        }
    }
}
//Метод уменьшения сдвига после удаления
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
}
//Коструктор узла дерева
bin_tree::tree_item::tree_item(patient* value){
    this->left = nullptr;
    this->right = nullptr;
    this->value = value;
}
//Деструктор узла дерева
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
//Метод добавления узла в дерево
void bin_tree::add_item(int key, unsigned int index){
    records += 1;
    tree_item** cur = &root;
    int level = 1;
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
    key_size = (key_size > std::to_string(key).length())? key_size : std::to_string(key).length();
    height = height < level ? level : height;
    *cur = new tree_item(new patient(key, index));
}
//Метод поиска в дереве
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
}
//Метод удаления из дерева
void bin_tree::remove_item(int key){
    tree_item** cur = &root;
    while(*cur){
        if((*cur)->value->card_num > key){
            cur = &((*cur)->left);
        }else if ((*cur)->value->card_num < key){
            cur = &((*cur)->right);
        }else{
            records -= 1;
            int ind = (*cur)->value->ind;
            if ((*cur)->left && (*cur)->right){
                //Если есть правый и левый ребёнок - заменяем удалённое значение
                //на минимальное справа
                tree_item** replacement = &((*cur)->right);
                while ((*replacement)->left){
                    replacement = &((*replacement)->left);
                }
                (*cur)->value->card_num = (*replacement)->value->card_num;
                (*cur)->value->ind = (*replacement)->value->ind;

                if ((*replacement)->right){
                    tree_item* temp = ((*replacement)->right);
                    (*replacement)->right = nullptr;
                    delete *replacement;
                    *replacement = temp;
                }else{
                    delete *replacement;
                    *replacement = nullptr;
                }
            //Иначе просто перемещаем ребёнка на место удалённого
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
            root->decr_ind(ind);
            break;
        }
    }
}
//Метод запуска вывода дерева
void bin_tree::print_tree(){
    std::string gap = "";
    for(int i = 0; i < key_size; i++){
        gap += " ";
    }
    if (root){
        root->print_self("", gap, false, false);
    }
}
//Конструктор обёртки дерева
bin_tree::bin_tree(){
    root = nullptr;
    height = 0;
    records = 0;
    key_size = 0;
}
//Деструктор обёртки дерева
bin_tree::~bin_tree(){
    if (root){
        delete root;
    }
}