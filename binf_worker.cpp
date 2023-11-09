#include "binf_worker.h"
binf_worker::binf_worker(){
    file.open("bininput.bin", std::ios::trunc | std::ios::in | std::ios::out | std::ios::binary);
    size = 0;
    binary_tree = new bin_tree();
}
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
}
int binf_worker::get_size(){
    return size;
}
void binf_worker::print_tree(){
    binary_tree->print_tree();
}
void binf_worker::write_to_file(patient_info& info){
    if (file.is_open()){
        file.seekp(0, std::ios::end);
        file.write(reinterpret_cast<char*>(&info), sizeof(info));
        binary_tree->add_item(info.card_num, size);
        ++size;
    }
}
void binf_worker::remove_from_file(unsigned int ind){
    if(file.is_open()){
        file.seekg(0, std::ios::beg);
        std::ofstream ofs("temp.bin", std::ios::out | std::ios::binary); 
        patient_info info;
        for (int i = 0; i < size; i++){
            if (i != ind){
                file.read(reinterpret_cast<char*>(&info), sizeof(patient_info));
                ofs.write(reinterpret_cast<char*>(&info), sizeof(patient_info));
            }else{
                file.seekg(sizeof(patient_info), std::ios::cur);
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
std::string binf_worker::find_in_file(unsigned int ind){
    std::string record;
    if(file.is_open() && ind <= (size-1)){
        patient_info info;
        file.seekg(ind*sizeof(info), std::ios::beg);
        file.read(reinterpret_cast<char*>(&info), sizeof(patient_info));
        record.append(std::to_string(info.card_num)+" ");
        record.append(info.illness);
        record.append(" ");
        record.append(info.doctor);
    }
    return record;
}
std::string binf_worker::find_by_bin_tree(int key){
    int ind = binary_tree->find_item(key);
    if (ind > 0){
        return find_in_file(ind);
    }
    return "Key "+std::to_string(key)+" not found";
}
std::string binf_worker::find_by_b_tree(int key){
    return "";
}
std::string binf_worker::find_by_hash_table(int key){
    return "";
}
binf_worker::~binf_worker(){
    delete binary_tree;
    file.close();
}