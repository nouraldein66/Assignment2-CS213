#ifndef VOLEMACHINESIMULATOR_REGISTER_H
#define VOLEMACHINESIMULATOR_REGISTER_H

#include "Machine.h"

const int REG_SIZE = 16;

class Register: public Machine{
private:
    int reg[REG_SIZE];
public:
    void getVal(int r);
    void load(int r);
};

#endif //VOLEMACHINESIMULATOR_REGISTER_H
