#include "Machine.h"
#include "Memory.h"


long long to_decimal(string s,int base = 16){
    long long ans{};
    int n= (int)s.size();
    for(int i{};i<n;i++)ans+=(s[i]-'0')*pow(base,n-i-1);
    return ans;
}

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
            cout << machine1.getPCVAl() << endl << endl;
            menu();
            break;
        case 2:
            cout << machine1.getIRVAl() << endl << endl;
            menu();
            break;
        case 3:
            machine1.printMem();
            menu();
            break;
        case 4:
            machine1.printReg();
            menu();
            break;
        default:
            break;

    }
}


int main() {

    ifstream inputFile("input.txt");

    string line;
    //a vector for storing instructions
    vector<string> instructions;
    
    if(inputFile.fail()) {
        cerr <<"Unable to open file." << endl;
    }

    while (getline(inputFile, line)) {
        instructions.emplace_back(line);
    }
    int startPoint = 160;

    //in this for loop we split each instruction into operator and operand
    //then store each instruction on the memory
    for(int i{} ; i < (int)instructions.size() ; ++i) {
        string ins = instructions[i];
        // getting each insturction
        vector<string> temp;    //stores the operator and operands in indices of temp
        string str {""};
        bool isX {false};   //because the file that we read from stores the instructions as hexa

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
                str.push_back(x);
        }

        if (!str.empty()) {
            temp.emplace_back(str);     //temp = {2,0,22}
        }

        if (temp.front().size() > 1) {
            cout << "Invalid Instruction." << endl;
            return 0;
        }

        // storing the instructions in the memory: the instruction will be split into two halves
        // each half is stored on a memory cell.
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


    }


    // this for loop is for splitting the instructions into operator and operands
    // and then implement them.
    for (auto ins: instructions) {
        // setting the IR and PC values
        machine1.setIR(startPoint);
        machine1.setPC(startPoint+2);
        // showing a menu
        menu();
        // getting each insturction
        vector<string> temp;    //stores the instructions and operands in indices of temp
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
            temp.emplace_back(str);     //temp = {2,0,22}
        }

        if (temp.front().size() > 1) {
            cout << "Invalid Instruction." << endl;
            return 0;
        }
        // storing the instruction in the memory

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
                }                       // temp = {5, 1, 2, 3}
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
