#include <iostream>
using namespace std;

int multiply(int num, int multiplier) {
    // Checks if one and only one of the numbers (num XOR multiplier) is 
    // negative by XOR-ing their sign bits
    bool neg = (num>>31) ^ (multiplier>>31);

    // Converts both numbers to positive values
    num = (num>>31) ? 0-num : num;
    multiplier = (multiplier>>31) ? 0-multiplier : multiplier;
    
    int result = 0;

    // While multiplier still has significant bits continue shifting and adding
    while (multiplier != 0) {
        // If the least significant bit of the multiplier is 1, add the current
        // value of num to the result
        if (multiplier & 1) {
            result += num;
        }
        // Shift num to the left by 1
        num <<= 1;
        // Shift multiplier to the right by 1
        multiplier >>= 1;
    }
    return result;
}

int main(void) {
    cout << multiply(-6, -3) << endl;
    return 0;
}