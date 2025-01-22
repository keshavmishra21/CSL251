#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> AddSub(const vector<int> &A, const vector<int> &B, bool subtract){
    int n = A.size();
    vector<int> result(n);
    vector<int> operandB = B;
    int carry = subtract ? 1 : 0;
    if(subtract){
        for(int i = 0; i < n; i++){
            operandB[i] = 1 - B[i];
        }
    }
    for(int i = n - 1; i >= 0; i--){
        int sum = A[i] + operandB[i] + carry;
        result[i] = sum % 2;
        carry = sum / 2;
    }
    return result;
}

int binaryToInteger(const vector<int> &binary){
    int n = binary.size();
    bool isNegative = binary[0] == 1;
    int decimal = 0;
    for(int i = 0; i < n; i++){
        decimal = (decimal << 1) + binary[i];
    }
    if(isNegative){
        decimal -= (1 << n);
    }
    return decimal;
}

int main(){
    int n;
    string binary1, binary2;
    cout << "Enter the number of bits (n): ";
    cin >> n;
    cout << "Enter the first binary number in 2's complement format (A): ";
    cin >> binary1;
    cout << "Enter the second binary number in 2's complement format (B): ";
    cin >> binary2;
    vector<int> A(n), B(n);
    for(int i = 0; i < n; i++){
        A[i] = binary1[i] - '0';
        B[i] = binary2[i] - '0';
    }
    vector<int> sum = AddSub(A, B, false);
    vector<int> diff = AddSub(A, B, true);
    cout << "A + B = ";
    for (int bit : sum)
    cout << bit;
    cout << " (" << binaryToInteger(sum) << " in decimal)" << endl;
    cout << "A - B = ";
    for (int bit : diff)
    cout << bit;
    cout << " (" << binaryToInteger(diff) << " in decimal)" << endl;
    return 0;
}