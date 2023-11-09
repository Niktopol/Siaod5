#ifndef STRUCTURES
#define STRUCTURES
#include <string>
struct patient{
    int card_num;
    int ind;
    bool operator == (const patient&);
    patient(int, int);
    patient();
};
struct patient_info{
    int card_num;
    char illness[8];
    char doctor[16];
    void set_fields(int, std::string, std::string);
};
#endif