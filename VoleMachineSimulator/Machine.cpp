#include "Machine.h"

void Machine::jump(int reg_address, int mem_address) {
    if (reg[reg_address] == reg[0]) {
        PC = mem_address;
    } else {
        ++++PC;
    }
}
