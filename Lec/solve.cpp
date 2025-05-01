#include <iostream>
#include <string>
using namespace std;

struct process {
    int arrivalTime, burstTime, priority, index;
    process() {
        this->arrivalTime = 0;
        this->burstTime = 0;
        this->priority = 0;
        this->index = 0;
    }

    process(int arrivalTime, int burstTime, int priority, int index) {
        this->arrivalTime = arrivalTime;
        this->burstTime = burstTime;
        this->priority = priority;
        this->index = index;
    }
};

void solve() {
    int numProcess;
    string algorithm;
    int quantum;

    cin >> numProcess >> algorithm; // Get num of processes + schedule algorithm
    if (algorithm == "RR") {        // If Round Robin algorithm, get quantum
        cin >> quantum;
    }

    process processes[numProcess];

    for (int i = 0; i < numProcess; i++){
        int arrivalTime, burstTime, priority;
        processes[i] = process(arrivalTime, burstTime, priority, i+1);
    }

    if (algorithm == "FCFS"){
        //Execute FCFS
    }
    if (algorithm == "SJF") {
        //Execute SJF
    }
    if (algorithm == "SRTF") {
        //Execute SRTF
    }
    if (algorithm == "P") {
        //Execute P
    }
    if (algorithm == "RR") {
        //Execute RR
    }
    
}

int main() {
    int numTestCase;

    cin >> numTestCase;

    for (int i = 1; i < numTestCase; i++) {
        cout << i << endl;
        solve();
    }
    return 0;
}