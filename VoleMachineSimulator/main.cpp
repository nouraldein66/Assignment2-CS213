#include "Machine.h"
#include "Memory.h"


bool checkSize(size_t size) {
    if (size != 3) {
        cout << "Invalid Instruction." << endl;
        return false;
    }
    return true;
}

Machine machine1;
Memory mem1;

void menu(){
    cout << "1) Get PC Value\n 2) Get IR Value\n 3) Get Memory Values\n 4) Get Registers values\n 5) continue\n";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            cout << machine1.getPCVAl() << endl;
            break;
        case 2:
            cout << machine1.getIRVAl() << endl;
            break;
        case 3:
            machine1.printMem();
            break;
        case 4:
            machine1.printReg();
            break;
        default:
            break;

    }
}

long long to_decimal(string s,int base = 16){
     long long ans{};
     int n= (int)s.size();
     for(int i{};i<n;i++)ans+=(s[i]-'0')*pow(base,n-i-1);
     return ans;
}



int main() {
    /*string fileName;
    cin >> fileName;

    ifstream inputFile(fileName+".txt");
*/
    string line;
    vector<string> instructions;
/*
    while (getline(inputFile, line)) {
        instructions.emplace_back(line);
    }

    for(auto i : instructions){
        cout << " " << i;
    }
*/

    for(int i = 0; i<5; ++i){
        getline(cin,line);
        instructions.push_back(line);
    }

    int startPoint = 160;

    for (auto ins: instructions) {
        machine1.setIR(startPoint);
        machine1.setPC(startPoint+2);

        menu();
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
            if(isX)
                str.push_back(x);   //2 0 22
        }

        if (!str.empty()) {
            temp.emplace_back(str);
        }

        if (temp.front().size() > 1) {
            cout << "Invalid Instruction." << endl;
            return 0;
        }
        string firstHalf, secondHalf;
        firstHalf = temp[0] + temp[1];
        if(temp.size() == 3)
            secondHalf = temp[2];
        else
            secondHalf = temp[2] + temp[3];

        long long value1 = to_decimal(firstHalf);
        long long value2 = to_decimal(secondHalf);

        machine1.setMemAddress(startPoint,value1);
        machine1.setMemAddress(startPoint+1,value2);
        startPoint+=2;

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
    menu();



    return 0;
}
