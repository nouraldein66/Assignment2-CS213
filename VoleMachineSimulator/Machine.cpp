#include "Machine.h"

Machine::Machine() {
    reg[REG_SIZE] = {0};
    IR = 0;
    PC = 0;
    mem[SIZE] = {0};
    ins = {'C', 0, 0, 0, 0};
}

void Machine::jump(int reg_address, int mem_address) {
    if (mem_address % 2 != 0 || (reg_address > 15 || reg_address < 0)) {
        cout << "Invalid Instruction." << endl;
        return;
    }
    if (reg[reg_address] == reg[0]) {
        PC = mem_address;
    } else {
        ++++PC;
    }
}

// Instruction 4, which copies the bit patterns found in register 1 to register 2
void Machine::copyRegisters(int register1, int register2) {
    reg[register2] = reg[register1];
    PC+=2;
}

//add the bit-patterns in R1 and R2 as two's complement
void Machine::ADDition(int targetRegister, int register1, int register2) {
    deque<int> B1 = binaryRepresentation(reg[register1]);
    deque<int> B2 = binaryRepresentation(reg[register2]);
    int twosComplement1 = 0, twosComplement2 = 0;

    if(B1[0] == 1)
        twosComplement1 = -(pow(2,B1.size()-1));
    if(B2[0] == 1)
        twosComplement2 = -(pow(2,B2.size()-1));

    for (int i = 1; i < B1.size(); ++i) {
        if(B1[i] == 1)
            twosComplement1+=(pow(2,B1.size()-i-1));
    }
    for (int i = 1; i < B2.size(); ++i) {
        if(B2[i] == 1)
            twosComplement2+=(pow(2,B2.size()-i-1));
    }

    reg[targetRegister] = twosComplement1 + twosComplement2;

    PC+=2;
}

deque<int> Machine::binaryRepresentation(int n){
    deque <int> dq;
    if(n == 0){
        dq.push_back(0);
    }

    while (n != 0) {
        dq.push_front(n%2);
        n /= 2;
    }
    return dq;
}

void Machine::Load(int op, int R, int value) {
    if(R >= REG_SIZE || R < 0)
    {
        cout<<"Invalid instruction\n";
        return;
    }
    reg[R] = value;
}

void Machine::Load(int R, int ad) {
    if(R >= REG_SIZE || R < 0 || ad > SIZE || ad < 0)
    {
        cout<<"Invalid instruction\n";
        return;
    }

    reg[R] = mem[ad];
}

void Machine::printReg() {
    for(int i=0; i<REG_SIZE; ++i){
        cout << "R" << i << ": " << hex << reg[i] << endl;
    }
}

void Machine::printMem() {
    for(int i=0; i<SIZE; ++i){
        cout << "M" << i << ": " << hex << mem[i] << endl;
    }
}
