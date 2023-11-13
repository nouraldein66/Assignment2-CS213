#include "Memory.h"

void Memory::store(int val, int ad) {
    if (ad == 0) {
        cout << hex << val << endl;
        return;
    }
    mem[ad] = val;
    ++++PC;
}
