#include <iostream>
using namespace std;

int multiply(int num, int multiplier) {
    bool neg = (num < 0) ^ (multiplier < 0);
    //checks if one and only one of the numbers is negative
    // Convert both numbers to positive values.
    unsigned int absNum = (num < 0) ? -num : num;
    unsigned int absMult = (multiplier < 0) ? -multiplier : multiplier;
    int result = 0;
    // While multiplier still has significant bits continue shifting and adding
    while (absMult != 0) {
        // If the least significant bit of the multiplier is 1 add the current
        // value of num to the result
        if (absMult & 1) {
            result += absNum;
        }

        // Shift num to the left by 1
        absNum <<= 1;

        // Shift multiplier to the right by 1
        absMult >>= 1;
    }
    return neg ? -result : result;
}

int main(void) {
    cout << multiply(-6, -3) << endl;
    return 0;
}