#ifndef VOLEMACHINESIMULATOR_REGISTER_H
#define VOLEMACHINESIMULATOR_REGISTER_H

#include "Machine.h"

class Register: public Machine{
private:
    int reg[SIZE];
public:
    void getVal(int r);
    void load(int r);
};

#endif //VOLEMACHINESIMULATOR_REGISTER_H
