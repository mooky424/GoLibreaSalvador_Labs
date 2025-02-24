#include <iostream>
using namespace std;
#include <chrono>

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
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    
    auto t1 = high_resolution_clock::now();

    for(int i = -500; i < 500; i++){
        for(int j = -500; j < 500; j++){
            multiply(i,j);
        }
    }
    auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    cout << ms_int.count() << "ms\n";
    cout << ms_double.count() << "ms\n";
    return 0;
}