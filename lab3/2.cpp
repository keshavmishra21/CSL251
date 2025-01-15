#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

vector<int> AddSub(const vector<int> &A, const vector<int> &B, bool subtract){
    int n = A.size();
    vector<int> result(n);
    vector<int> operandB = B;
    int carry = subtract ? 1 : 0;
    if(subtract){
        for (int i = 0; i < n; i++){
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

vector<int> boothsAlgorithm(int n, vector<int> A, vector<int> M, vector<int> Q){
    int Q_1 = 0;
    int Count = n;
    while(Count > 0){
        int Q_0 = Q.back();
        if(Q_0 == 1 && Q_1 == 0){
            A = AddSub(A, M, true);
        }
        else if(Q_0 == 0 && Q_1 == 1){
            A = AddSub(A, M, false);
        }
        Q_1 = Q.back();
        Q.pop_back();
        Q.insert(Q.begin(), A.back());
        A.pop_back();
        A.insert(A.begin(), A[0]);
        --Count;
    }
    vector<int> result = A;
    result.insert(result.end(), Q.begin(), Q.end());
    return result;
}

int stringToInteger(const string &binary){
    int n = binary.size();
    bool isNegative = binary[0] == '1';
    int decimal = 0;
    for(int i = 0; i < n; i++){
        decimal = (decimal << 1) + (binary[i] - '0');
    }
    if(isNegative){
        decimal -= (1 << n);
    }
    return decimal;
}

vector<int> integerToBinary(int num, int n){
    vector<int> binary(n);
    for(int i = n - 1; i >= 0; i--){
        binary[i] = (num & 1);
        num >>= 1;
    }
    return binary;
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
    cout << "Enter the first binary number in 2's complement format (multiplicand): ";
    cin >> binary1;
    cout << "Enter the second binary number in 2's complement format (multiplier): ";
    cin >> binary2;
    vector<int> multiplicand = integerToBinary(stringToInteger(binary1), n);
    vector<int> multiplier = integerToBinary(stringToInteger(binary2), n);
    vector<int> resultBinary = boothsAlgorithm(n, vector<int>(n, 0), multiplicand, multiplier);
    cout << "A * B = ";
    for (int bit : resultBinary)
    cout << bit;
    cout << endl << "Result in decimal: " << binaryToInteger(resultBinary) << endl;
    return 0;
}