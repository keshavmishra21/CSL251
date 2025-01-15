#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int stringToInteger(const string &binary){
    int n = binary.size();
    bool isNegative = binary[0] == '1';
    int decimal = 0;
    for(int i = 0; i < n; ++i){
        decimal = (decimal << 1) + (binary[i] - '0');
    }
    if(isNegative){
        decimal -= (1 << n);
    }
    return decimal;
}

int boothsAlgorithm(int n, int multiplicand, int multiplier){
    int A = 0;
    int Q = multiplier;
    int M = multiplicand;
    int Q_1 = 0;
    int count = n;
    while(count > 0){
        int LSB = Q & 1;
        if (LSB == 1 && Q_1 == 0) {
            A -= M;
        } else if (LSB == 0 && Q_1 == 1) {
            A += M;
        }
        Q_1 = LSB;
        int combined = (A << n) | (Q & ((1 << n) - 1));
        combined >>= 1;
        A = combined >> n;
        Q = combined & ((1 << n) - 1);
        count--;
    }
    return (A << n) | Q;
}

int main(){
    int n;
    string binary1, binary2;
    cout<<"Enter the number of bits (n): ";
    cin>>n;
    cout<<"Enter the first binary number in 2's complement format(multiplicand): ";
    cin>>binary1;
    cout<<"Enter the second binary number in 2's complement format(multiplier): ";
    cin>>binary2;
    int multiplicand = stringToInteger(binary1);
    int multiplier = stringToInteger(binary2);
    int result = boothsAlgorithm(n, multiplicand, multiplier);
    cout<<"Result in decimal: "<<result<<endl;
    return 0;
}