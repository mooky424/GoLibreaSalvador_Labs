#include <iostream>
using namespace std;

int multiply(int num, int multiplier) {
    int result = 0;
    
    // Checks if multiplier is negative by 
    bool neg = multiplier < 0 ? 1 : 0;

    // Calculates absolute value of multiplier
    multiplier = neg ? -multiplier : multiplier;

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
    return neg ? -result : result;
}

int main(void) {
    cout << multiply(-6, -3) << endl;
    return 0;
}