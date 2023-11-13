#ifndef VOLEMACHINESIMULATOR_MACHINE_H
#define VOLEMACHINESIMULATOR_MACHINE_H

#include <bits/stdc++.h>

using namespace std;

const int SIZE = 256;

class Machine {
private:
    int IR;
    int PC;
public:
    void getIRVAl();
    void getPCVAl();
};

#endif //VOLEMACHINESIMULATOR_MACHINE_H
