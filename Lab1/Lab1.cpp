#include <iostream>

bool bit[32], r, command;
float f;
short int in;
unsigned short num;
unsigned short k[32];
const short int MAX_S = 32767;
const float MAX_F = 340282346638528859811704183484516925440.000000;

union type {
    float f;
    int I;
};

void outBitShort() {
    std::cout << "Number representation " << in << " in IEEE Format: ";
    for (int i = 0; i < 16; i++)
        std::cout << bit[i];
    std::cout << std::endl;
}

void outBitFloat() {
    std::cout << "Number representation  " << f << " in IEEE Format: ";
    for (int i = 0; i < 32; i++)
        std::cout << bit[i];
    std::cout << std::endl;
}

void checkNumFloat() {
    while (num > 31) {
        std::cin.clear();
        std::cin.ignore(MAX_S, '\n');
        std::cout << "Incorrect entry of the number of bits, the required number is from 0 to 31. Try again. \n";
        std::cout << "The number of bits you don't want to invert: ";
        std::cin >> num;
    }
}

void checkNumShort() {
    while (num > 15) {
        std::cin.clear();
        std::cin.ignore(MAX_S, '\n');
        std::cout << "Incorrect entry of the number of bits, the required number is from 0 to 15. Try again. \n";
        std::cout << "The number of bits you don't want to invert: ";
        std::cin >> num;
    }
}

void suffix(int t) {
    if (t + 1 == 1)
        std::cout << t + 1 << "st bit you don't want to invert:  ";
    else if (t + 1 == 2)
        std::cout << t + 1 << "nd bit you don't want to invert:  ";
    else if(t + 1 == 3)
        std::cout << t + 1 << "rd bit you don't want to invert:  ";
    else
        std::cout << t + 1 << "th bit you don't want to invert:";
}

void notReverseCheck(long long t, unsigned short k[], unsigned short l) {
    while (k[t] > l) {
        std::cout << "incorrect bit input format, required input range is from 1 to  " << l << ". Try again. \n";
        std::cout << "Re-enter: ";
        std::cin >> k[t];
    }
}

bool floatToBit(float f) {
    type data;
    data.f = f;
    for (int i = 0; i < 32; i++)
        bit[i] = (data.I >> (32 - i - 1) & 1);
    outBitFloat();
    return bit;
}

bool shortToBit(short input) {
    for (int i = 0; i < 16; i++)
        bit[i] = ((input >> (16 - i - 1)) & 1);
    outBitShort();
    return bit;
}

unsigned short* prepareToReverseFloat() {
    std::cout << "The number of bits you don't want to invert:  ";
    std::cin >> num;
    checkNumFloat();
    for (int t = 0; t < num; t++) {
        suffix(t);
        std::cin >> k[t];
        notReverseCheck(t, k, 31);
    }
    return k;
}

unsigned short* prepareToReverseShort() {
    std::cout << "The number of bits you don't want to invert:  ";
    std::cin >> num;
    checkNumShort();
    for (int t = 0; t < num; t++) {
        suffix(t);
        std::cin >> k[t];
        notReverseCheck(t, k, 15);
    }
    return k;
}

void outRevFloat() {
    std::cout << "Inverse bit value of a number  " << f << ":\n";
    std::cout << "--------------------------------------------\n";
    std::cout << "| S[] |   P[]   |            M[]           |\n";
    std::cout << "--------------------------------------------\n";
    for (int i = 0; i < 32; i++){
        if( i == 0){
            std::cout << "|  ";
            std::cout << bit[i];
            std::cout << "  |";
        }
        else if (i < 8){
            if(i == 1)
                std::cout << " ";
            std::cout << bit[i];
            if (i == 7)
                std::cout << " |";
        }
        else{
            if(i == 8)
                std::cout << " ";
            std::cout << bit[i];
            if(i == 31)
                std::cout << " |\n";
        }
    }
    std::cout << "--------------------------------------------\n";
}

void outRevShort() {
    std::cout << "Inverse bit value of a number  " << in << ":\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "| S[] |             P[]                 |\n";
    std::cout << "-----------------------------------------\n";
    for (int i = 0; i < 16; i++){
        if(i == 0){
            std::cout << "|  ";
            std::cout << bit[i];
            std::cout << "  |";
        }
        else{
            if(i == 1)
                std::cout << "        ";
            std::cout << bit[i];
            if(i == 15)
                std::cout << "          |\n";
        }
    }
    std::cout << "-----------------------------------------\n";
}

bool reverseFloat() {
    floatToBit(f);
    prepareToReverseFloat();
    for (int i = 0; i < 32; i++)
        for (int j = 0; j < num; j++)
            if (i != 32 - k[j])
                bit[i] = (bit[i] == 1) ? 0 : 1;
    outRevFloat();
    return bit;
}


bool reverseShort() {
    shortToBit(in);
    prepareToReverseShort();
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < num; j++)
            if (i != 16 - k[j])
                bit[i] =  (bit[i] == 1) ? 0 : 1;
    outRevShort();
    return bit;
}

void firstCase() {
    std::cout << "Enter a number in float format: ";
    std::cin >> f;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(MAX_F, '\n');
        std::cout << "The selected number is not in the specified range float(" << MAX_F * (-1) - 1 << " -- " << MAX_F << "). Try again.\n";
        std::cout << "Enter a number in float format: ";
        std::cin >> f;
    }
    reverseFloat();
}

void secondCase() {
    std::cout << "Enter a number in short int format: ";
    std::cin >> in;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(MAX_S, '\n');
        std::cout << "The selected number is not in the specified range short ( " << MAX_S * (-1) - 1 << " -- " << MAX_S << "). Try again. \n";
        std::cout << "Enter a number in short int format: ";
        std::cin >> in;
    }
    reverseShort();
}

void error() {
    std::cout << "Invalid data selection entry. \n";
    std::cout << std::endl;
}

void outputRepeat(){
    std::cout << "Select the number of which data type you want to invert the values: \n";
    std::cout << "0 -- float;\n";
    std::cout << "1 -- short int;\n";
    std::cout << "Input: ";
    std::cin >> command;
}

void output() {
    outputRepeat();
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1, '\n');
        error();
        outputRepeat();
    }
}

void loop() {
    std::cout << "Do you want to continue? Yes - 1; No - 0: ";
    std::cout << std::endl;
    std::cin >> r;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1, '\n');
        r = 0;
    }
    std::cout << std::endl;
}

void body(){
    do {
        output();
        command == 0 ? firstCase() : (command == 1) ? secondCase() : error();
        loop();
    } while (r == 1);
    std::cout << "Thanks for using the program! \n";
}

int main() {
    body();
}
