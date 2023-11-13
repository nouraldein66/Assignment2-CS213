#ifndef VOLEMACHINESIMULATOR_MACHINE_H
#define VOLEMACHINESIMULATOR_MACHINE_H

#include <bits/stdc++.h>

using namespace std;

const int SIZE = 256;

struct Instruction {
    int op;
    int register1;
    int register2;
    int register3;
    int memory;
};

class Machine {
private:
    int IR;
    int PC;
protected:
    Instruction ins;
public:
    void getIRVAl();
    void getPCVAl();
    void jump(int reg_address, int mem_address);
};


#endif //VOLEMACHINESIMULATOR_MACHINE_H
