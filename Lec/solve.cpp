#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct process {
    int arrivalTime, burstTime, priority, index, firstResponse;
    process() {
        this->arrivalTime = 0;
        this->burstTime = 0;
        this->priority = 0;
        this->index = 0;
        this->firstResponse = 0;
    }

    process(int arrivalTime, int burstTime, int priority, int index) {
        this->arrivalTime = arrivalTime;
        this->burstTime = burstTime;
        this->priority = priority;
        this->index = index;
        this->firstResponse = 0;
    }
};

struct statistics {
    int totalBurst, totalArrival, totalTermination, totalFirstResponse;
    statistics() {
        this->totalBurst = 0;
        this->totalArrival = 0;
        this->totalTermination = 0;
        this->totalFirstResponse = 0;
    }
    statistics(int totalBurst, int totalArrival, int totalTermination,
               int totalFirstResponse) {
        this->totalBurst = totalBurst;
        this->totalArrival = totalArrival;
        this->totalTermination = totalTermination;
        this->totalFirstResponse = totalFirstResponse;
    }
};

struct sortArrival {
    bool operator()(const process &a, const process &b) {
        if (a.arrivalTime == b.arrivalTime) {
            return a.burstTime > b.burstTime;
        }
        return a.arrivalTime > b.arrivalTime;
    }
};

struct sortBurst {
    bool operator()(const process &a, const process &b) {
        if (a.burstTime == b.burstTime) {
            return a.arrivalTime > b.arrivalTime;
        }
        return a.burstTime > b.burstTime;
    }
};

struct sortPriority {
    bool operator()(const process &a, const process &b) {
        if (a.priority == b.priority) {
            return a.burstTime > b.burstTime;
        }
        return a.priority < b.priority;
    }
};

struct sortRoundRobin {
    bool operator()(const process &a, const process &b) {
        if (a.priority >= 0 and b.priority >= 0) {
            if (a.arrivalTime == b.arrivalTime) {
                return a.burstTime > b.burstTime;
            }
            return a.arrivalTime > b.arrivalTime;
        } else {
            if (a.arrivalTime == b.arrivalTime) {
                return a.priority < b.priority;
            }
            return a.arrivalTime > b.arrivalTime;
        }
    }
};

void fcfs(priority_queue<process, vector<process>, sortArrival> arrivalQueue,
          int numProcess) {

    priority_queue<process, vector<process>, sortArrival> currProcesses;
    statistics stats;
    int done = 0;
    int clock = 0;
    int start = 0;

    // Execute processes
    process p; // Keep track of current process
    while (done < numProcess) {
        // Get processes to be executed at 0
        while (!arrivalQueue.empty() and
               arrivalQueue.top().arrivalTime <= clock) {
            process next = arrivalQueue.top();
            arrivalQueue.pop();
            currProcesses.push(next);
        }

        if (!currProcesses.empty()) {
            p = currProcesses.top();
            currProcesses.pop();

            cout << clock << " " << p.index << " ";
            cout << p.burstTime << "X" << endl;
            done++;

            if (p.firstResponse == 0) {
                p.firstResponse = clock;
            }
            stats.totalArrival += p.arrivalTime;
            stats.totalBurst += p.burstTime;
            stats.totalFirstResponse += p.firstResponse;
            stats.totalTermination += clock + p.burstTime;

            clock += p.burstTime;
        } else {
            clock++;
        }
    }
}

void sjf(priority_queue<process, vector<process>, sortArrival> arrivalQueue,
         int numProcess) {

    priority_queue<process, vector<process>, sortBurst> currProcesses;
    statistics stats;
    int done = 0;
    int clock = 0;
    int start = 0;

    // Execute processes
    process p; // Keep track of current process
    while (done < numProcess) {

        // Get processes to be executed at clock time
        while (!arrivalQueue.empty() and
               arrivalQueue.top().arrivalTime <= clock) {
            process next = arrivalQueue.top();
            arrivalQueue.pop();
            currProcesses.push(next);
        }

        if (!currProcesses.empty()) {
            p = currProcesses.top();
            currProcesses.pop();

            cout << clock << " " << p.index << " ";
            cout << p.burstTime << "X" << endl;
            done++;

            if (p.firstResponse == 0) {
                p.firstResponse = clock;
            }
            stats.totalArrival += p.arrivalTime;
            stats.totalBurst += p.burstTime;
            stats.totalFirstResponse += p.firstResponse;
            stats.totalTermination += clock + p.burstTime;

            clock += p.burstTime;
        } else {
            clock++;
        }
    }
}

void srtf(priority_queue<process, vector<process>, sortArrival> arrivalQueue,
          int numProcess) {

    priority_queue<process, vector<process>, sortBurst> currProcesses;
    statistics stats;
    int done = 0;
    int clock = 0;
    int start = 0;

    // Get process/es for time = 0

    process p;
    while (done < numProcess) {

        while (!arrivalQueue.empty() and
               arrivalQueue.top().arrivalTime <= clock) {
            process next = arrivalQueue.top();
            arrivalQueue.pop();
            currProcesses.push(next);
        }

        if (p.index != currProcesses.top().index) {
            if (p.index != 0) {
                cout << start << " " << p.index << " " << clock - start
                     << ((p.burstTime == 0) ? "X" : "") << endl;
            }
            start = clock;
        }

        if (!currProcesses.empty()) { // Execute per time tick

            // Get process to be executed
            p = currProcesses.top();
            currProcesses.pop();

            // Execute one burst
            p.burstTime--;
            stats.totalBurst += 1;

            if (p.firstResponse == 0) {
                p.firstResponse = clock;
            }

            // If burst > 0 put back in queue
            if (p.burstTime > 0) {
                currProcesses.push(p);
            } else {
                done++;
                stats.totalArrival += p.arrivalTime;
                stats.totalFirstResponse += p.firstResponse;
                stats.totalTermination += clock + 1;
            }
        }
        clock++;

        if (currProcesses.empty()) {
            cout << start << " " << p.index << " " << clock - start
                 << ((p.burstTime == 0) ? "X" : "") << endl;
        }
    }
}

void prio(priority_queue<process, vector<process>, sortArrival> arrivalQueue,
          int numProcess) {

    priority_queue<process, vector<process>, sortPriority> currProcesses;
    statistics stats;
    int done = 0;
    int clock = 0;
    int start = 0;

    // Get process/es for time = 0

    process p;
    while (done < numProcess) {

        while (!arrivalQueue.empty() and
               arrivalQueue.top().arrivalTime <= clock) {
            process next = arrivalQueue.top();
            arrivalQueue.pop();
            currProcesses.push(next);
        }

        if (p.index != currProcesses.top().index) {
            if (p.index != 0) {
                cout << start << " " << p.index << " " << clock - start
                     << ((p.burstTime == 0) ? "X" : "") << endl;
            }
            start = clock;
        }

        if (!currProcesses.empty()) { // Execute per time tick

            // Get process to be executed
            p = currProcesses.top();
            currProcesses.pop();

            // Execute one burst
            p.burstTime--;
            stats.totalBurst += 1;

            if (p.firstResponse == 0) {
                p.firstResponse = clock;
            }

            // If burst > 0 put back in queue
            if (p.burstTime > 0) {
                currProcesses.push(p);
            } else {
                done++;
                stats.totalArrival += p.arrivalTime;
                stats.totalFirstResponse += p.firstResponse;
                stats.totalTermination += clock + 1;
            }
        }
        clock++;

        if (currProcesses.empty()) {
            cout << start << " " << p.index << " " << clock - start
                 << ((p.burstTime == 0) ? "X" : "") << endl;
        }
    }
}

void rr(priority_queue<process, vector<process>, sortArrival> arrivalQueue,
        int numProcess, int quantum) {

    priority_queue<process, vector<process>, sortRoundRobin> currProcesses;
    int done = 0;
    int clock = 0;
    int start = 0;

    // Get process/es for time = 0

    process p;
    while (done < numProcess) {

        while (!arrivalQueue.empty() and
               arrivalQueue.top().arrivalTime <= clock) {
            process next = arrivalQueue.top();
            arrivalQueue.pop();
            currProcesses.push(next);
        }

        if (!currProcesses.empty()) { // Execute per time tick

            // Get process to be executed
            p = currProcesses.top();
            currProcesses.pop();

            int delta = (p.burstTime < quantum) ? p.burstTime : quantum;

            // Execute one burst
            p.burstTime -= delta;

            // If burst > 0 put back in queue
            if (p.burstTime > 0) {
                process delta_p =
                    process(clock + delta, p.burstTime, -1, p.index);
                currProcesses.push(delta_p);
            } else {
                done++;
            }
            cout << clock << " " << p.index << " " << delta
                 << ((p.burstTime == 0) ? "X" : "") << endl;

            clock += delta;

        } else {
            clock++;
        }
    }
}

void getCriteria() {}

void solve() {
    int numProcess;
    string algorithm;
    int quantum;

    cin >> numProcess >> algorithm; // Get num of processes + schedule algorithm
    if (algorithm == "RR") {        // If Round Robin algorithm, get quantum
        cin >> quantum;
    }

    priority_queue<process, vector<process>, sortArrival> processes;

    for (int i = 0; i < numProcess; i++) {
        int arrivalTime, burstTime, priority;
        cin >> arrivalTime >> burstTime >> priority;
        processes.push(process(arrivalTime, burstTime, priority, i + 1));
    }

    if (algorithm == "FCFS") {
        fcfs(processes, numProcess);
    }
    if (algorithm == "SJF") {
        sjf(processes, numProcess);
    }
    if (algorithm == "SRTF") {
        srtf(processes, numProcess);
    }
    if (algorithm == "P") {
        prio(processes, numProcess);
    }
    if (algorithm == "RR") {
        rr(processes, numProcess, quantum);
    }
}

int main() {
    int numTestCase;

    cin >> numTestCase;

    for (int i = 0; i < numTestCase; i++) {
        cout << i + 1 << endl;
        solve();
    }
    return 0;
}