#ifndef VOLEMACHINESIMULATOR_MACHINE_H
#define VOLEMACHINESIMULATOR_MACHINE_H

#include <bits/stdc++.h>

using namespace std;

const int SIZE = 256;
const int REG_SIZE = 16;

struct Instruction {
    char op;
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
    int mem[SIZE];
    int PC;
    Instruction ins;
public:
    Machine();
    void printMem();
    void printReg();
    void setIR(int ir){IR = ir;}
    void setPC(int pc){PC = pc;}
    void setMemAddress(int address, int value){
        mem[address] = value;
    }
    int getIRVAl() {return IR;}
    int getPCVAl() {return PC;}
    int getVal(size_t i) {return reg[i];}
    void Load(int op , int R , int value);
    void Load(int R , int ad);
    void jump(int reg_address, int mem_address);
    void copyRegisters(int register1, int register2);   //copy the bit patterns in R1 to R2
    void ADDition(int targetRegister, int register1, int register2);
    deque<int> binaryRepresentation(int n);
};

#endif //VOLEMACHINESIMULATOR_MACHINE_H
