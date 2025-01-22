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

int stringToInteger(const string &binary){
    int n = binary.size();
    int decimal = 0;
    for(int i = 0; i < n; i++){
        decimal = (decimal << 1) + (binary[i] - '0');
    }
    return decimal;
}

vector<int> integerToBinary(int num, int n){
    vector<int> binary(n, 0);
    for(int i = n - 1; i >= 0; i--){
        binary[i] = num % 2;
        num /= 2;
    }
    return binary;
}

int binaryToInteger(const vector<int> &binary){
    int n = binary.size();
    int decimal = 0;
    for(int i = 0; i < n; i++){
        decimal = (decimal << 1) + binary[i];
    }
    return decimal;
}

void UnsignedBinaryDivision(int n, vector<int> M, vector<int> Q){
    vector<int> A(n, 0);
    int count = n;
    while(count > 0){
        for(int i = 0; i < n - 1; i++){
            A[i] = A[i + 1];
        }
        A[n - 1] = Q[0];
        for(int i = 0; i < n - 1; i++){
            Q[i] = Q[i + 1];
        }
        Q[n - 1] = 0;
        A = AddSub(A, M, true);
        if(A[0] == 1){
            Q[n - 1] = 0;
            A = AddSub(A, M, false);
        }
        else{
            Q[n - 1] = 1;
        }
        count--;
    }

    cout << "Quotient (Q): ";
    for(int bit : Q) 
    cout << bit;
    cout << " (" << binaryToInteger(Q) << " in decimal)" << endl;

    cout << "Remainder (A): ";
    for (int bit : A)
    cout << bit;
    cout << " (" << binaryToInteger(A) << " in decimal)" << endl;
}

int main(){
    int n;
    string binaryDivisor, binaryDividend;
    cout << "Enter the number of bits (n): ";
    cin >> n;
    cout << "Enter the divisor in 2's complement binary format (M): ";
    cin >> binaryDivisor;
    cout << "Enter the dividend in 2's complement binary format (Q): ";
    cin >> binaryDividend;
    vector<int> M = integerToBinary(stringToInteger(binaryDivisor), n);
    vector<int> Q = integerToBinary(stringToInteger(binaryDividend), n);
    UnsignedBinaryDivision(n, M, Q);
    return 0;
}
