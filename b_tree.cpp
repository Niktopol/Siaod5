#include "b_tree.h"

//Метод для уменьшения сдвига при удалениии элемента
void b_tree::tree_item::decrease_ind(unsigned int key){
    for(int i = 0; i < val_count; i++){
        if (values[i]->ind > key){
            values[i]->ind -= 1;
        }
    }
    if(has_children){
        for(int i = 0; i < val_count+1; i++){
            children[i]->decrease_ind(key);
        }
    }
}
//Метод добавления значения в массив узла с сохранением сортировки
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
//Метод добавления ребёнка для узла
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
//Метод удаления значения из узла со сдивгом остальных влево
void b_tree::tree_item::remove_val(unsigned int ind){
    delete values[ind];
    for(int i = ind; i < val_count-1; i++){
        values[i] = values[i+1];
    }
    values[val_count-1] = nullptr;
    val_count -= 1;
}
//Метод удаления ребёнка из узла со сдивгом остальных влево
void b_tree::tree_item::remove_child(unsigned int ind){
    if (children[ind]){
        delete children[ind];
    }
    for(int i = ind; i < (param*2-1); i++){
        children[i] = children[i+1];
    }
    children[param*2-1] = nullptr;
}
//Метод поиска в дереве
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
//Метод рекурсивной распечатки дерева
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
            std::cout << gap_before.substr(0, gap_before.length()-1) + "└";
        }else if ((i == val_count-1) && right){
            std::cout << gap_before.substr(0, gap_before.length()-1) + "┌";
        }else if (gap_before.length() > 0){
            std::cout << gap_before.substr(0, gap_before.length()-1) + "├";
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
//Конструктор узла
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
//Деструктор узла
b_tree::tree_item::~tree_item(){
    for(int i = 0; i < (param*2-1); i++){
        delete values[i];
    }
    for(int i = 0; i < (param*2); i++){
        delete children[i];
    }
    delete [] values;
    delete [] children;
}
//Метод для разбиения узла и получения левой половины
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
//Метод для разбиения узла и получения правой половины
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
//Метод добавления узла
void b_tree::add_item(int key, unsigned int index){
    int level = 1;
    if(!root){
        root = new tree_item(param);
        records = 1;
    }
    tree_item* parent = nullptr;
    tree_item* cur = root;
    while (true){
        //Если текущий узел полон - разбиваем его на два и передаём центральное узначение узлу выше
        if (cur->val_count == (param*2-1)){
            transform_count += 1;
            tree_item* left = get_left_part(cur);
            tree_item* right = get_right_part(cur);
            records += 1;
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
                records += 1;
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
        //Когда дошли до листа - можно добавлять
        if (!cur->has_children){
            if (cur->add_val(key, index)){
                key_size = (key_size > std::to_string(key).length())? key_size : std::to_string(key).length();
                //records += 1;
            }
            break;
        }
        //Иначе продолжаем поиск нужного листа
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
//Метод запуска поиска в дереве
int b_tree::find_item(int key){
    if (root){
        return root->find_item(key);
    }
    return -1;
}
//Метод удаления значения из дерева
void b_tree::remove_item(int key){
    if(root){
        int ind = -1;
        tree_item* parent = nullptr;
        tree_item* cur = root;
        //Т.к. удалить можно только из листа - спускаемся в лист
        while(cur->has_children){
            int left = 0;
            int right = cur->val_count-1;
            int mid = 0;
            while (true){
                mid = (left + right) / 2;
                if (key < cur->values[mid]->card_num){
                    right = mid - 1;
                }
                else if (key > cur->values[mid]->card_num){
                    left = mid + 1;
                }
                else{
                    //Если удаляемое значение не в листе
                    ind = (ind > 0) ? ind: cur->values[mid]->ind;
                    //И в левом ребёнке нужного значения достаточно значений
                    //Меняем удаляемый элемент на наибольший в поддереве с корнем - левым ребёнком
                    //И удаляем этот наибольший в левом поддереве
                    if(cur->children[mid]->val_count >= param){
                        tree_item* temp_cur = cur->children[mid];
                        while (temp_cur->has_children){
                            temp_cur = temp_cur->children[temp_cur->val_count];
                        }
                        cur->values[mid]->card_num = temp_cur->values[temp_cur->val_count-1]->card_num;
                        cur->values[mid]->ind = temp_cur->values[temp_cur->val_count-1]->ind;
                        key = temp_cur->values[temp_cur->val_count-1]->card_num;
                        parent = cur;
                        cur = cur->children[mid];
                    //Если в правом ребёнке нужного значения достаточно значений
                    //Меняем удаляемый элемент на наименьший в поддереве с корнем - правым ребёнком
                    //И удаляем этот наименьший в правом поддереве
                    }else if(cur->children[mid+1]->val_count >= param){
                        tree_item* temp_cur = cur->children[mid+1];
                        while (temp_cur->has_children){
                            temp_cur = temp_cur->children[0];
                        }
                        cur->values[mid]->card_num = temp_cur->values[0]->card_num;
                        cur->values[mid]->ind = temp_cur->values[0]->ind;
                        key = temp_cur->values[0]->card_num;
                        parent = cur;
                        cur = cur->children[mid+1];
                    }else{
                        //Иначе объединяем левого и правого ребёнка, 
                        //переносим удаляемый элемент в узел - результат объединения
                        //и запускаем удаление из этого узла
                        tree_item* left_neighbour = cur->children[mid];
                        tree_item* right_neighbour = cur->children[mid+1];
                        left_neighbour->add_val(cur->values[mid]->card_num, cur->values[mid]->ind);
                        for(int i = 0; i < right_neighbour->val_count; i++){
                            left_neighbour->children[left_neighbour->val_count] = right_neighbour->children[i];
                            right_neighbour->children[i] = nullptr;
                            left_neighbour->add_val(right_neighbour->values[i]->card_num, right_neighbour->values[i]->ind);
                        }
                        left_neighbour->children[left_neighbour->val_count] = right_neighbour->children[right_neighbour->val_count];
                        right_neighbour->children[right_neighbour->val_count] = nullptr;
                        cur->remove_child(mid+1);
                        cur->remove_val(mid);
                        parent = cur;
                        if((cur == root) && (cur->val_count == 0)){
                            root = cur->children[0];
                            cur->children[0] = nullptr;
                            delete cur;
                            parent = nullptr;
                        }
                        cur = left_neighbour;
                    }
                    break;
                }
                if (left > right){
                    int found_ind = mid;
                    if (key < cur->values[mid]->card_num){
                        parent = cur;
                        cur = cur->children[mid];
                    }else{
                        parent = cur;
                        cur = cur->children[mid+1];
                        found_ind += 1;
                    }
                    //Если в текущем узле недостаточно элементов - нужно дополнить
                    if(cur->val_count == (param-1)){
                        //При возможности взять элемент из левого брата
                        if((found_ind > 0) && (parent->children[found_ind-1]->val_count >= param)){
                            tree_item* left_neighbour = parent->children[found_ind-1];
                            cur->add_val(parent->values[found_ind-1]->card_num, parent->values[found_ind-1]->ind);
                            parent->values[found_ind-1]->card_num = left_neighbour->values[left_neighbour->val_count-1]->card_num;
                            parent->values[found_ind-1]->ind = left_neighbour->values[left_neighbour->val_count-1]->ind;
                            for(int i = cur->val_count; i > 0; i--){
                                cur->children[i] = cur->children[i-1];
                            }
                            cur->children[0] = left_neighbour->children[left_neighbour->val_count];

                            left_neighbour->children[left_neighbour->val_count] = nullptr;
                            left_neighbour->remove_val(left_neighbour->val_count-1);
                        //Или из правого
                        }else if(((found_ind+1) < param*2) && parent->children[found_ind+1] && parent->children[found_ind+1]->val_count >= param){
                            tree_item* right_neighbour = parent->children[found_ind+1];
                            cur->add_val(parent->values[found_ind]->card_num, parent->values[found_ind]->ind);
                            parent->values[found_ind]->card_num = right_neighbour->values[0]->card_num;
                            parent->values[found_ind]->ind = right_neighbour->values[0]->ind;
                            cur->children[cur->val_count] = right_neighbour->children[0];

                            right_neighbour->children[0] = nullptr;
                            right_neighbour->remove_child(0);
                            right_neighbour->remove_val(0);
                        }else{
                            //Иначе, объединить с каким либо братом и разделяющим значением из родителя
                            if(found_ind > 0){
                                tree_item* left_neighbour = parent->children[found_ind-1];
                                left_neighbour->add_val(parent->values[found_ind-1]->card_num, parent->values[found_ind-1]->ind);
                                for(int i = 0; i < cur->val_count; i++){
                                    left_neighbour->children[left_neighbour->val_count] = cur->children[i];
                                    cur->children[i] = nullptr;
                                    left_neighbour->add_val(cur->values[i]->card_num, cur->values[i]->ind);
                                }
                                left_neighbour->children[left_neighbour->val_count] = cur->children[cur->val_count];
                                cur->children[cur->val_count] = nullptr;
                                parent->remove_child(found_ind);
                                cur = left_neighbour;
                                parent->remove_val(found_ind-1);
                            }else{
                                tree_item* right_neighbour = parent->children[found_ind+1];
                                cur->add_val(parent->values[found_ind]->card_num, parent->values[found_ind]->ind);
                                for(int i = 0; i < right_neighbour->val_count; i++){
                                    cur->children[cur->val_count] = right_neighbour->children[i];
                                    right_neighbour->children[i] = nullptr;
                                    cur->add_val(right_neighbour->values[i]->card_num, right_neighbour->values[i]->ind);
                                }
                                cur->children[cur->val_count] = right_neighbour->children[right_neighbour->val_count];
                                right_neighbour->children[right_neighbour->val_count] = nullptr;
                                parent->remove_child(found_ind+1);
                                parent->remove_val(found_ind);
                            }
                            if((parent == root) && (parent->val_count == 0)){
                                root = parent->children[0];
                                parent->children[0] = nullptr;
                                delete parent;
                                parent = nullptr;
                            }
                        }
                    }
                    break;
                }
            }
        }
        //Когда дошли до листа - ищем и удаляем
        int l_left = 0;
        int l_right = cur->val_count-1;
        int l_mid = 0;
        while (true){
            l_mid = (l_left + l_right) / 2;
            if (key < cur->values[l_mid]->card_num){
                l_right = l_mid - 1;
            }
            else if (key > cur->values[l_mid]->card_num){
                l_left = l_mid + 1;
            }
            else{
                ind = (ind > 0) ? ind : cur->values[l_mid]->ind;
                cur->remove_val(l_mid);
                root->decrease_ind(ind);
                return;
            }
            if (l_left > l_right){
                return;
            }
        }
    }
}
//Метод запуска вывода дерева
void b_tree::print_tree(){
    std::string gap = "";
    for(int i = 0; i < key_size; i++){
        gap += " ";
    }
    root->print_self("", gap, false, false);
}
//Конструктор обёртки дерева
b_tree::b_tree(int param){
    if (param > 1){
        this->param = param;
        root = nullptr;
        records = 0;
        key_size = 0;
        height = 0;
        transform_count = 0;
    }else{
        std::__throw_length_error("Wrong tree parameter");
    }
}
//Деструктор обёртки дерева
b_tree::~b_tree(){
    if (root){
        delete root;
    }
}