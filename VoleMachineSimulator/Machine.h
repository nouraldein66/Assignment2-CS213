#ifndef VOLEMACHINESIMULATOR_MACHINE_H
#define VOLEMACHINESIMULATOR_MACHINE_H

#include <bits/stdc++.h>

using namespace std;

const int SIZE = 256;
const int REG_SIZE = 16;

struct Instruction {
    int op;
    int register1;
    int register2;
    int register3;
    int memory;
};

class Machine {
private:
    int reg[REG_SIZE];
    int IR;
protected:
    int PC;
    Instruction ins;
public:
    void getIRVAl();
    void getPCVAl();
    void jump(int reg_address, int mem_address);
};

#endif //VOLEMACHINESIMULATOR_MACHINE_H
