#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// Struct for Processes to be used in executing scheduling algorithms
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

// Struct for process statistics for calculating criteria per each processes
struct processStats {
    int termination, burst, arrival, firstResponse;
    processStats() {
        this->arrival = 0;
        this->burst = 0;
        this->firstResponse = -1;
        this->termination = 0;
    }
};

// Struct for cpu statistics for calculating total criteria for CPU
struct cpuStats {
    int totalBurst, totalArrival, totalTermination, totalFirstResponse,
        numProcesses, finalClock;
    cpuStats() {
        this->totalArrival = 0;
        this->totalBurst = 0;
        this->totalFirstResponse = 0;
        this->totalTermination = 0;
        this->numProcesses = 0;
        this->finalClock = 0;
    }
    cpuStats(int numProcesses) {
        this->totalBurst = 0;
        this->totalArrival = 0;
        this->totalTermination = 0;
        this->totalFirstResponse = 0;
        this->numProcesses = numProcesses;
        this->finalClock = 0;
    }
};

// Sort by Arrival time (earliest first)
// If same arrival time, index
struct sortArrival {
    bool operator()(const process &a, const process &b) {
        if (a.arrivalTime == b.arrivalTime) {
            return a.index > b.index;
        }
        return a.arrivalTime > b.arrivalTime;
    }
};

// Sort by Burst time (shortest first)
// If same burst time, FCFS
// If same arrival time, index
struct sortBurst {
    bool operator()(const process &a, const process &b) {
        if (a.burstTime == b.burstTime) {
            if (a.arrivalTime == b.arrivalTime) {
                return a.index > b.index;
            }
            return a.arrivalTime > b.arrivalTime;
        }
        return a.burstTime > b.burstTime;
    }
};

// Sort by Prirority
// If same priority, SJF
// If same arrival, FCFS
// If same burst, index
struct sortPriority {
    bool operator()(const process &a, const process &b) {
        if (a.priority == b.priority) {
            if (a.burstTime == b.burstTime) {
                if (a.arrivalTime == b.arrivalTime) {
                    return a.index > b.index;
                }
                return a.arrivalTime > b.arrivalTime;
            }
            return a.burstTime > b.burstTime;
        }
        return a.priority < b.priority;
    }
};

// Sort for Round Robin
// Preempted processes always go behind new processes
// Preempted:
// If both preempted, FCFS,
// If same arrival time, SJF
// If same burst time, index
// New:
// If both new, FCFS
// If same arrival time, SJF
// If same burst time, index
struct sortRoundRobin {
    bool operator()(const process &a, const process &b) {
        if (a.priority == -1 && b.priority == -1) {
            if (a.arrivalTime == b.arrivalTime) {
                if (a.burstTime == b.burstTime) {
                    return a.index > b.index;
                }
                return a.burstTime > b.burstTime;
            }
            return a.arrivalTime > b.arrivalTime;
        } else if (a.priority == -1) {
            return true;
        } else if (b.priority == -1) {
            return false;
        }

        if (a.arrivalTime == b.arrivalTime) {
            if (a.burstTime == b.burstTime) {
                return a.index > b.index;
            }
            return a.burstTime > b.burstTime;
        }
        return a.arrivalTime > b.arrivalTime;
    }
};

// Function to get Criteria based statistics gathered
// stats = stats of total CPU processes (final clock, num processes)
// statsMap = stats of each CPU process in a map
void getCriteria(cpuStats stats, map<int, processStats> statsMap) {

    // Tally all statistics from each process
    for (auto &[index, process] : statsMap) {
        stats.totalArrival += process.arrival;
        stats.totalBurst += process.burst;
        stats.totalFirstResponse += process.firstResponse;
        stats.totalTermination += process.termination;
    }

    // Calculate CPU Statistics
    // CPU Util = Total Burst / Total Time Elapsed (Final Clock)
    float cpuUtil = (float)stats.totalBurst / stats.finalClock * 100;

    // CPU Throughput = No. of Processes / Total Time Elapsed (Final Clock)
    float throughput = (float)(stats.numProcesses) / stats.finalClock;

    // Average CPU Waiting Time
    // = (Total Turnaround Time - Total Burst Time) / No. of Processes
    float waitingTime = (float)(stats.totalTermination - stats.totalArrival -
                                stats.totalBurst) /
                        stats.numProcesses;

    // Average CPU Turnaround Time
    // = (Total Termination Time - Total Arrival Time) / No. of Processes
    float turnaround = (float)(stats.totalTermination) -
                       (float)(stats.totalArrival) / stats.numProcesses;

    // Average CPU Response Time
    // = (Total Response Time - Total Arrival Time) / No. of Processes
    float responseTime =
        (float)(stats.totalFirstResponse - stats.totalArrival) /
        stats.numProcesses;

    cout << "Total time elapsed: " << stats.finalClock << "ns" << endl;
    cout << "Total CPU burst time: " << stats.totalBurst << "ns" << endl;
    cout << "CPU Utilization: " << cpuUtil << "%" << endl;

    cout << "Throughput: " << throughput << " processes/ns" << endl;

    cout << "Waiting Times: " << endl;
    for (auto &[index, process] : statsMap) {
        cout << " ";
        cout << "Process " << index << ": ";
        cout << process.termination - process.arrival - process.burst << "ns";
        cout << endl;
    }

    cout << "Average waiting time: "
         << (float)(stats.totalTermination - stats.totalArrival -
                    stats.totalBurst) /
                stats.numProcesses
         << "ns" << endl;

    cout << "Turnaround Times: " << endl;
    for (auto &[index, process] : statsMap) {
        cout << " ";
        cout << "Process " << index << ": ";
        cout << process.termination - process.arrival << "ns";
        cout << endl;
    }

    cout << "Average turnaround time: "
         << (float)(stats.totalTermination - stats.totalArrival) /
                stats.numProcesses
         << "ns" << endl;

    cout << "Response Times: " << endl;
    for (auto &[index, process] : statsMap) {
        cout << " ";
        cout << "Process " << index << ": ";
        cout << process.firstResponse - process.arrival << "ns";
        cout << endl;
    }

    cout << "Average response time: "
         << (float)(stats.totalFirstResponse - stats.totalArrival) /
                stats.numProcesses
         << "ns" << endl;
}

template <typename Comparator>
void nonPreemptive(
    Comparator algo, map<int, processStats> statsMap,
    priority_queue<process, vector<process>, sortArrival> arrivalQueue,
    int numProcess) {

    // Priority Queue, sorted by Comparator
    priority_queue<process, vector<process>, Comparator> currProcesses(algo);
    cpuStats stats(numProcess);
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

        // Execute each process depending on sorting in currProcesses queue
        if (!currProcesses.empty()) {
            p = currProcesses.top();
            currProcesses.pop();

            cout << clock << " " << p.index << " ";
            cout << p.burstTime << "X" << endl;
            done++;

            // Record First Response if not recorded yet
            if (statsMap[p.index].firstResponse == -1) {
                statsMap[p.index].firstResponse = clock;
            }

            // Record Termination
            statsMap[p.index].termination = clock + p.burstTime;

            // Increment clock by burst time
            clock += p.burstTime;
        } else { // if no processes to be executed increment clock
            clock++;
        }
    }
    stats.finalClock = clock; // Record Final statistics
    getCriteria(stats, statsMap);
}

template <typename Comparator>
void preemptive(
    Comparator algo, map<int, processStats> statsMap,
    priority_queue<process, vector<process>, sortArrival> arrivalQueue,
    int numProcess) {

    priority_queue<process, vector<process>, Comparator> currProcesses(algo);
    cpuStats stats(numProcess);
    int done = 0;
    int clock = 0;
    int start = 0;

    process p;
    while (done < numProcess) {
        // cout << "Clock: " << clock << endl;
        while (!arrivalQueue.empty() and
               arrivalQueue.top().arrivalTime <= clock) {
            process next = arrivalQueue.top();
            arrivalQueue.pop();
            currProcesses.push(next);
        }

        if (p.index != 0) {
            if (p.index != currProcesses.top().index) {
                cout << start << " " << p.index << " " << clock - start
                     << ((p.burstTime == 0) ? "X" : "") << endl;
                start = clock;
            }
        }

        if (!currProcesses.empty()) { // Execute per time tick

            // Get process to be executed
            p = currProcesses.top();
            currProcesses.pop();

            // Execute one burst
            p.burstTime--;

            // Record response time if not recorded yet
            if (statsMap[p.index].firstResponse == -1) {
                statsMap[p.index].firstResponse = clock;
            }

            // If burst > 0 put back in queue
            if (p.burstTime > 0) {
                currProcesses.push(p);
            } else {
                done++;
                // Record termination time
                statsMap[p.index].termination += clock + 1;
            }
        }

        // If waiting for next process adjust start time
        if (arrivalQueue.empty() and currProcesses.empty()) {
            if (p.index == 0) {
                start = clock;
            }
        }

        clock++;

        if (done == numProcess) {
            cout << start << " " << p.index << " " << clock - start
                 << ((p.burstTime == 0) ? "X" : "") << endl;
        }
    }
    stats.finalClock = clock;
    getCriteria(stats, statsMap);
}

void rr(priority_queue<process, vector<process>, sortArrival> arrivalQueue,
        map<int, processStats> statsMap, int numProcess, int quantum) {

    priority_queue<process, vector<process>, sortRoundRobin> currProcesses;
    cpuStats stats(numProcess);
    int done = 0;
    int clock = 0;

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

            // Execute one quantum
            p.burstTime -= delta;

            // R
            if (statsMap[p.index].firstResponse == -1) {
                statsMap[p.index].firstResponse = clock;
            }

            // If burst > 0 put back in queue
            if (p.burstTime > 0) {
                process delta_p =
                    process(clock + delta, p.burstTime, -1, p.index);
                currProcesses.push(delta_p);
            } else {
                done++;
                statsMap[p.index].termination += clock + delta;
            }
            cout << clock << " " << p.index << " " << delta
                 << ((p.burstTime == 0) ? "X" : "") << endl;

            clock += delta;

        } else {
            clock++;
        }
    }
    stats.finalClock = clock;
    getCriteria(stats, statsMap);
}

void solve(int testcase) {
    int numProcess;
    string algorithm;
    int quantum;

    cin >> numProcess >> algorithm; // Get num of processes + schedule algorithm
    if (algorithm == "RR") {        // If Round Robin algorithm, get quantum
        cin >> quantum;
    }

    
    priority_queue<process, vector<process>, sortArrival> processes;
    map<int, processStats> statsMap;
    
    for (int i = 0; i < numProcess; i++) {
        
        int arrivalTime, burstTime, priority;
        cin >> arrivalTime >> burstTime >> priority;
        processes.push(process(arrivalTime, burstTime, priority, i + 1));
        
        processStats stats;
        stats.arrival = arrivalTime;
        stats.burst = burstTime;
        statsMap[i + 1] = stats; // i + 1 is the process index
    }
    
    cout << testcase << " " << algorithm << endl;

    if (algorithm == "FCFS") {

        sortArrival algo;
        nonPreemptive(algo, statsMap, processes, numProcess);
    }
    if (algorithm == "SJF") {
        sortBurst algo;
        nonPreemptive(algo, statsMap, processes, numProcess);
    }
    if (algorithm == "SRTF") {
        sortBurst algo;
        preemptive(algo, statsMap, processes, numProcess);
    }
    if (algorithm == "P") {
        sortPriority algo;
        preemptive(algo, statsMap, processes, numProcess);
    }
    if (algorithm == "RR") {
        rr(processes, statsMap, numProcess, quantum);
    }
}

int main() {
    int numTestCase;

    cin >> numTestCase;

    for (int i = 0; i < numTestCase; i++) {
        solve(i + 1);
    }
    return 0;
}