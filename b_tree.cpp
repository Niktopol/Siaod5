#include "b_tree.h"

bool b_tree::tree_item::add_val(int key, unsigned int index){
    int temp_key = 0;
    int temp_ind = 0;
    for(int i = 0; i < val_count; i++){
        if(values[i]->card_num == key){
            return false; 
        }
        if(values[i]->card_num > key){
            temp_key = values[i]->card_num;
            temp_ind = values[i]->ind;
            values[i]->card_num = key;
            values[i]->ind = index;
            key = temp_key;
            index = temp_ind;
        }
    }
    values[val_count] = new patient(key, index);
    val_count += 1;
    return true;
}
void b_tree::tree_item::add_children(tree_item* to_replace, tree_item* left, tree_item* right){
    for(int i = 0; i < (param*2); i++){
        if (children[i] == to_replace){
            children[i] = left;
            for(int j = i+1; j < (param*2); j++){
                left = children[j];
                children[j] = right;
                right = left;
            }
            break;
        }
    }
}
void b_tree::tree_item::remove_val(unsigned int ind){
    delete values[ind];
    for(int i = ind; i < val_count-1; i++){
        values[i] = values[i+1];
    }
    values[val_count-1] = nullptr;
    val_count -= 1;
}
void b_tree::tree_item::remove_child(unsigned int ind){
    delete children[ind];
    for(int i = ind; i < (param*2-1); i++){
        children[i] = children[i+1];
    }
    children[param*2-1] = nullptr;
}
int b_tree::tree_item::find_item(int key){
    int left = 0;
    int right = val_count-1;
    int mid = 0;
	while (true){
		mid = (left + right) / 2;
		if (key < values[mid]->card_num){
            right = mid - 1;
        }
		else if (key > values[mid]->card_num){
            left = mid + 1;
        }
		else{
            return values[mid]->ind;
        }
		if (left > right){
            if(has_children){
                if (key < values[mid]->card_num){
                    return children[mid]->find_item(key);
                }else{
                    return children[mid+1]->find_item(key);
                }
            }else{
                return -1;
            }
        }
	}
}
void b_tree::tree_item::remove_and_unite(int key, unsigned int found_ind){
    int left = 0;
    int right = val_count-1;
    int mid = 0;
    while (true){
        mid = (left + right) / 2;
        if (key < values[mid]->card_num){
            right = mid - 1;
        }
        else if (key > values[mid]->card_num){
            left = mid + 1;
        }
        if (left > right){
            int found_pos = mid;
            if (key > values[mid]->card_num){
                found_pos += 1;
            }
            if((found_pos > 0) && (children[found_pos-1]->val_count > (param-1))){
                children[found_pos]->add_val(values[found_pos-1]->card_num, values[found_pos-1]->ind);
                values[found_pos-1]->card_num = children[found_pos-1]->values[children[found_pos-1]->val_count-1]->card_num;
                values[found_pos-1]->ind = children[found_pos-1]->values[children[found_pos-1]->val_count-1]->ind;
                children[found_pos-1]->remove_val(children[found_pos-1]->val_count-1);
            }else if(children[found_pos+1]->val_count > (param-1)){
                children[found_pos]->add_val(values[found_pos]->card_num, values[found_pos]->ind);
                values[found_pos]->card_num = children[found_pos+1]->values[0]->card_num;
                values[found_pos]->ind = children[found_pos+1]->values[0]->ind;
                children[found_pos+1]->remove_val(0);
            }else{
                if(found_pos > 0){
                    for(int i = 0; i < children[found_pos]->val_count; i++){
                        children[found_pos-1]->add_val(children[found_pos]->values[i]->card_num, children[found_pos]->values[i]->ind);
                    }
                    children[found_pos-1]->add_val(values[found_pos-1]->card_num, values[found_pos-1]->ind);
                }else{
                    for(int i = 0; i < children[found_pos]->val_count; i++){
                        children[found_pos+1]->add_val(children[found_pos]->values[i]->card_num, children[found_pos]->values[i]->ind);
                    }
                    children[found_pos+1]->add_val(values[found_pos]->card_num, values[found_pos]->ind);
                }
                remove_child(found_pos);
                remove_val(mid);
            }
            return;
        }
    }
}
void b_tree::tree_item::remove_item(int key, tree_item* parent){
    int left = 0;
    int right = val_count-1;
    int mid = 0;
	while (true){
		mid = (left + right) / 2;
		if (key < values[mid]->card_num){
            right = mid - 1;
        }
		else if (key > values[mid]->card_num){
            left = mid + 1;
        }
		else{
            if(!has_children){
                if((val_count > param-1) || !parent){
                    remove_val(mid);
                }else{
                    remove_val(mid);
                    parent->remove_and_unite(key, mid);
                }
            }else{
                if(children[mid]->val_count > (param-1)){
                    values[mid]->card_num = children[mid]->values[children[mid]->val_count-1]->card_num;
                    values[mid]->ind = children[mid]->values[children[mid]->val_count-1]->ind;
                    children[mid]->remove_item(children[mid]->values[children[mid]->val_count-1]->card_num, this);
                }else if(children[mid+1]->val_count > (param-1)){
                    values[mid]->card_num = children[mid+1]->values[0]->card_num;
                    values[mid]->ind = children[mid+1]->values[0]->ind;
                    children[mid+1]->remove_item(children[mid+1]->values[0]->card_num, this);
                }else{
                    //join
                }
            }
            return;
        }
		if (left > right){
            if(has_children){
                if (key < values[mid]->card_num){
                    children[mid]->remove_item(key, this);
                    return;
                }else{
                    children[mid+1]->remove_item(key, this);
                    return;
                }
            }else{
                return;
            }
        }
	}
}
void b_tree::tree_item::print_self(std::string gap_before, std::string self_gap, bool left, bool right){
    for (int i = val_count-1; i >= 0; i--){
        if(children[i+1]){
            if (i == val_count-1){
                if((gap_before.length() > 0) && right){
                    children[i+1]->print_self(gap_before.substr(0, gap_before.length()-1)+" "+self_gap.substr(0, self_gap.length()-1) + "|", self_gap, false, true);
                }else{
                    children[i+1]->print_self(gap_before+self_gap.substr(0, self_gap.length()-1) + "|", self_gap, false, true);
                }
            }else{
                children[i+1]->print_self(gap_before+self_gap.substr(0, self_gap.length()-1) + "|", self_gap, false, false);
            }
        }
        if ((i == 0) && left){
            std::cout << gap_before.substr(0, gap_before.length()-1) + "\\";
        }else if ((i == val_count-1) && right){
            std::cout << gap_before.substr(0, gap_before.length()-1) + "/";
        }else if (gap_before.length() > 0){
            std::cout << gap_before.substr(0, gap_before.length()-1) + ">";
        }
        for (int j = 0; j < self_gap.length() - std::to_string(values[i]->card_num).length(); j++){
            std::cout << " ";
        }
        std::cout << values[i]->card_num << std::endl;
    }
    if(children[0]){
        if((gap_before.length() > 0) && left){
            children[0]->print_self(gap_before.substr(0, gap_before.length()-1)+" "+self_gap.substr(0, self_gap.length()-1) + "|", self_gap, true, false);
        }else{
            children[0]->print_self(gap_before+self_gap.substr(0, self_gap.length()-1) + "|", self_gap, true, false);
        }
    }
}
b_tree::tree_item::tree_item(int param){
    val_count = 0;
    has_children = false;
    values = new patient*[param*2-1];
    children = new tree_item*[param*2];
    for(int i = 0; i < (param*2-1); i++){
        values[i] = nullptr;
    }
    for(int i = 0; i < (param*2); i++){
        children[i] = nullptr;
    }
    this->param = param;
}
b_tree::tree_item::~tree_item(){
    for(int i = 0; i < (param*2-1); i++){
        if (values[i]){
            delete values[i];
        }
    }
    for(int i = 0; i < (param*2); i++){
        if (children[i]){
            delete children[i];
        }
    }
    delete [] values;
    delete [] children;
}
b_tree::tree_item* b_tree::get_left_part(tree_item* node){
    tree_item* left_part = new tree_item(param);
    left_part->val_count = param-1;
    for(int i = 0; i < param-1; i++){
        left_part->values[i] = node->values[i];
        node->values[i] = nullptr;
    }
    if(node->has_children){
        left_part->has_children = true;
        for(int i = 0; i < param; i++){
            left_part->children[i] = node->children[i];
            node->children[i] = nullptr;
        }
    }
    return left_part;
}
b_tree::tree_item* b_tree::get_right_part(tree_item* node){
    tree_item* right_part = new tree_item(param);
    right_part->val_count = param-1;
    for(int i = 0; i < param-1; i++){
        right_part->values[i] = node->values[i+param];
        node->values[i+param] = nullptr;
    }
    if(node->has_children){
        right_part->has_children = true;
        for(int i = 0; i < param; i++){
            right_part->children[i] = node->children[i+param];
            node->children[i+param] = nullptr;
        }
    }
    return right_part;
}
void b_tree::add_item(int key, unsigned int index){
    int level = 1;
    if(!root){
        root = new tree_item(param);
    }
    tree_item* parent = nullptr;
    tree_item* cur = root;
    while (true){
        if (cur->val_count == (param*2-1)){
            tree_item* left = get_left_part(cur);
            tree_item* right = get_right_part(cur);
            if (parent){
                parent->add_children(cur, left, right);
                parent->add_val(cur->values[param-1]->card_num, cur->values[param-1]->ind);
            }else{
                tree_item* new_root = new tree_item(param);
                new_root->add_val(cur->values[param-1]->card_num, cur->values[param-1]->ind);
                new_root->has_children = true;
                new_root->children[0] = left;
                new_root->children[1] = right;
                root = new_root;
                level += 1;
            }
            if (key <= cur->values[param-1]->card_num){
                delete cur;
                cur = left;
            }else{
                delete cur;
                cur = right;
            }
        }
        if (!cur->has_children){
            if (cur->add_val(key, index)){
                key_size = (key_size > std::to_string(key).length())? key_size : std::to_string(key).length();
                records += 1;
            }
            break;
        }
        parent = cur;
        int i = 0;
        for(; (key > cur->values[i]->card_num) && ((i+1) < cur->val_count); i++);
        level += 1;
        if(key < cur->values[i]->card_num){
            cur = cur->children[i];
        }else if(key > cur->values[i]->card_num){
            cur = cur->children[i+1];
        }else{
            return;
        }
    }
    height = height < level ? level : height;
}
int b_tree::find_item(int key){
    if (root){
        return root->find_item(key);
    }
    return -1;
}
void b_tree::remove_item(int key){
    if(root){
        root->remove_item(key, nullptr);
    }
}
void b_tree::print_tree(){
    std::string gap = "";
    for(int i = 0; i < key_size; i++){
        gap += " ";
    }
    root->print_self("", gap, false, false);
}
b_tree::b_tree(int param){
    if (param > 1){
        this->param = param;
        root = nullptr;
        records = 0;
        key_size = 0;
        height = 0;
    }else{
        std::__throw_length_error("Wrong tree parameter");
    }
}
b_tree::~b_tree(){
    if (root){
        delete root;
    }
}