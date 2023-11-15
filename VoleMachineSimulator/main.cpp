#include "Machine.h"
#include "Memory.h"

bool checkSize(size_t size) {
    if (size != 3) {
        cout << "Invalid Instruction." << endl;
        return false;
    }
    return true;
}

int main() {
    string fileName;
    cin >> fileName;

    ifstream inputFile(fileName);

    string line;
    vector<string> instructions;

    while (getline(inputFile, line)) {
        instructions.emplace_back(line);
    }

    Machine machine1;
    Memory mem1;

    for (auto ins: instructions) {
        vector<string> temp;
        string str {""};
        bool isX {false};

        for (const auto &x: ins) {
            if (x == 'x' || x == 'X') {
                isX = true;
                continue;
            }

            if (x == ' ') {
                isX = false;
                temp.emplace_back(str);
                str = "";
                continue;
            }
            str.push_back(x);
        }

        if (!str.empty()) {
            temp.emplace_back(str);
        }

        if (temp.front().size() > 1) {
            cout << "Invalid Instruction." << endl;
            return 0;
        }
        char op_code = temp.front()[0];
        switch (op_code) {
            case '1':
                if (checkSize(temp.size())) {
                    machine1.Load(stoi(temp[1]), stoi(temp[2]));
                }
                break;

            case '2':
                if (checkSize(temp.size())) {
                    machine1.Load(2, stoi(temp[1]),stoi(temp[2]));
                }
                break;

            case '3':
                if (checkSize(temp.size())) {
                    mem1.store(machine1.getVal(stoi(temp[1])), stoi(temp[2]));
                }
                break;

            case '4':
                if (temp.size() != 4) {
                    cout << "Invalid Instruction." << endl;
                    return 0;
                }
                machine1.copyRegisters(stoi(temp[2]), stoi(temp[3]));
                break;
            case '5':
                if (temp.size() != 4) {
                    cout << "Invalid Instruction." << endl;
                    return 0;
                }
                machine1.ADDition(stoi(temp[1]), stoi(temp[2]), stoi(temp[3]));
                break;

            case 'B':
                if (checkSize(temp.size())) {
                    machine1.jump(stoi(temp[1]), stoi(temp[2]));
                }
                break;
            case 'C':
                if (stoi(temp[1]) != 0 || stoi(temp[2]) != 0) {
                    cout << "Invalid Instruction." << endl;
                }
                return 0;
                break;
            default:
                cout << "Invalid Instruction." << endl;
                return 0;
        }
    }



    return 0;
}
