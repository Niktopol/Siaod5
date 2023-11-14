#include "binf_worker.h"
//Конструктор объекта управления файлом
binf_worker::binf_worker(){
    file.open("bininput.bin", std::ios::trunc | std::ios::in | std::ios::out | std::ios::binary);
    size = 0;
    binary_tree = new bin_tree();
    btree = new b_tree(3);
    table = new hash_table();
}
//Метод создания файла
void binf_worker::gen_file(unsigned int size){
    std::ofstream fout("input.txt", std::ios::trunc | std::ios::out);
    std::string surnames [15] = {"Petrov", "Ivanov", "Sidorov", "Efimov", "Pahomov",
                                 "Dmitrov", "Palmov", "Pechkin", "Ptichkin", "Butilkin", 
                                 "Lyamkin", "Shishkin", "Medvedko", "Lemenko", "Muhinko"};
    if (fout.is_open()){
        for (int i = 0; i < size; i++){
            std::string data = std::to_string(1000000+rand()%9000000)+' ' + char(65+rand()%26) + std::to_string(10+rand()%90) + ' ' + surnames[rand()%15];
            fout << data << std::endl;
        }
        fout.close();
    }

    std::ifstream fin("input.txt");
    if (fin.is_open()){
        patient_info info;
        for (int i = 0; i < size; i++){
            fin >> info.card_num;
            fin >> info.illness;
            fin >> info.doctor;
            write_to_file(info);
        }
        fin.close();
    }
    std::cout << "File creation finished" << std::endl;
}
//Метод получения размера файла
int binf_worker::get_size(){
    return size;
}
//Метод вывода бинарного дерева
void binf_worker::print_binary_tree(){
    binary_tree->print_tree();
}
//Метод вывода b-дерева
void binf_worker::print_b_tree(){
    btree->print_tree();
}
//Метод вывода хэш-таблицы
void binf_worker::print_hash_table(){
    table->print_table();
}
//Метод записи в бинарный файл
void binf_worker::write_to_file(patient_info& info){
    if (file.is_open()){
        file.seekp(0, std::ios::end);
        file.write(reinterpret_cast<char*>(&info), sizeof(info));

        binary_tree->add_item(info.card_num, size);
        btree->add_item(info.card_num, size);
        table->push_key(info.card_num, size);
        
        ++size;
    }
}
//Метод удаления из бинарных файлов и используемых структур
void binf_worker::remove_from_file(int key){
    if(file.is_open()){
        file.seekg(0, std::ios::beg);
        std::ofstream ofs("temp.bin", std::ios::out | std::ios::binary); 
        patient_info info;
        for (int i = 0; i < size; i++){
            file.read(reinterpret_cast<char*>(&info), sizeof(patient_info));
            if (info.card_num != key){
                ofs.write(reinterpret_cast<char*>(&info), sizeof(patient_info));
            }else{
                binary_tree->remove_item(key);
                btree->remove_item(key);
                table->remove(key);
            }
        }
        ofs.close(); 
        file.close();
        remove("bininput.bin");
        rename("temp.bin", "bininput.bin"); 
        file.open("bininput.bin", std::ios::in | std::ios::out | std::ios::binary);
        --size;
    }
}
//Метод считывания записи по сдвигу
std::string binf_worker::find_in_file(int ind){
    std::string record;
    if(file.is_open() && ind < size && ind >= 0){
        patient_info info;
        file.seekg(ind*sizeof(info), std::ios::beg);
        file.read(reinterpret_cast<char*>(&info), sizeof(patient_info));
        record.append(std::to_string(info.card_num)+" ");
        record.append(info.illness);
        record.append(" ");
        record.append(info.doctor);
    }else{
        return "Record not found";
    }
    return record;
}
//Метод поиска с помощью бинарного дерева
std::string binf_worker::find_by_bin_tree(int key){
    return find_in_file(binary_tree->find_item(key));
}
//Метод поиска с помощью b-дерева
std::string binf_worker::find_by_b_tree(int key){
    return find_in_file(btree->find_item(key));
}
//Метод поиска с помощью хэш-таблицы
std::string binf_worker::find_by_hash_table(int key){
    return find_in_file(table->find(key));
}
//Деструктор объекта управления файлом
binf_worker::~binf_worker(){
    delete binary_tree;
    delete btree;
    delete table;
    file.close();
}