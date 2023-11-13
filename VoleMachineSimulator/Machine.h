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
    Instruction ins;
    int IR;
    int PC;
public:
    void getIRVAl();
    void getPCVAl();
};


#endif //VOLEMACHINESIMULATOR_MACHINE_H
