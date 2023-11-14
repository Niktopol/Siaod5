#include <iostream>
#include "binf_worker.h"
#include "structures.h"
#include <string>
#include <chrono>

int main(){
    srand(time(nullptr));
    binf_worker worker;
    int size;
    patient_info info;
    int card_num;
    std::string illness;
    std::string doctor;
    std::string cmd;

    std::cout << "Enter generated file size" << std::endl;
    std::cin >> size;
    worker.gen_file(size);
    while (true){
        std::cout << "Enter a command" << std::endl;
        std::cin >> cmd;
        if (cmd == "Add"){
            std::cout << "Enter card number: ";
            std::cin >> card_num;
            std::cout << "Enter illness code: ";
            std::cin >> illness;
            std::cout << "Enter doctor's surname: ";
            std::cin >> doctor;
            info.set_fields(card_num, illness, doctor);
            worker.write_to_file(info);
        }else if(cmd == "Binary-find"){
            std::cout << "Enter card number: ";
            std::cin >> card_num;
            auto begin = std::chrono::high_resolution_clock::now();
            std::cout << worker.find_by_bin_tree(card_num) << std::endl;
            std::cout << "Search finished in: " << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - begin).count() << " ns" << std::endl;
        }else if(cmd == "B-find"){
            std::cout << "Enter card number: ";
            std::cin >> card_num;
            auto begin = std::chrono::high_resolution_clock::now();
            std::cout << worker.find_by_b_tree(card_num) << std::endl;
            std::cout << "Search finished in: " << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - begin).count() << " ns" << std::endl;
        }else if(cmd == "Hash-find"){
            std::cout << "Enter card number: ";
            std::cin >> card_num;
            auto begin = std::chrono::high_resolution_clock::now();
            std::cout << worker.find_by_hash_table(card_num) << std::endl;
            std::cout << "Search finished in: " << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - begin).count() << " ns" << std::endl;
        }else if(cmd == "Binary-print"){
            worker.print_binary_tree();
        }else if(cmd == "B-print"){
            worker.print_b_tree();
        }else if(cmd == "Hash-print"){
            worker.print_hash_table();
        }else if(cmd == "Delete"){
            std::cout << "Enter card number: ";
            std::cin >> card_num;
            worker.remove_from_file(card_num);
        }else{
            break;
        }
    }
   
    return 0;
}