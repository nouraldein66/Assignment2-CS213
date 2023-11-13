#ifndef VOLEMACHINESIMULATOR_MEMORY_H
#define VOLEMACHINESIMULATOR_MEMORY_H

#include "Machine.h"

class Memory: public Machine {
private:
    int mem[SIZE];
public:
    int getVal(int ad);
    void store(int val, int ad);
};

#endif //VOLEMACHINESIMULATOR_MEMORY_H
