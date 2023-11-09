#include "structures.h"
bool patient::operator == (const patient& compared){
    return (this->card_num == compared.card_num && this->ind == compared.ind);
}
patient::patient(int card_num, int ind){
    this->card_num = card_num;
    this->ind = ind;
}
patient::patient(){
    this->card_num = 0;
    this->ind = -1;
}
void patient_info::set_fields(int card_num, std::string illness, std::string doctor){
    this->card_num = card_num;
    for (int i = 0; i < (illness.size() < 7? illness.size() : 7); i++){
        this->illness[i] = illness.at(i);
        if (i+1 == (illness.size() < 7? illness.size() : 7)){
            this->illness[i+1] = '\0';
        }
    }
    for (int i = 0; i < (doctor.size() < 15? doctor.size() : 15); i++){
        this->doctor[i] = doctor.at(i);
        if (i+1 == (doctor.size() < 15? doctor.size() : 15)){
            this->doctor[i+1] = '\0';
        }
    }
}