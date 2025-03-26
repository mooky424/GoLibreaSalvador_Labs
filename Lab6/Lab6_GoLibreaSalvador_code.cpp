#include <ctime>
#include <iostream>
#include <unistd.h>
#include <wait.h>

using namespace std;

int main() {

    pid_t pid = fork();

    if (pid < 0) {
        return -1;
    }

    if (pid == 0) {
        int myXclock = execlp("/usr/bin/xclock", "myXclock", NULL);
        return -1;
    } else {
        int counter = 0;
        while (true) {
            time_t now = time(NULL);
            struct tm *timeInfo = localtime(&now);
            char formattedTime[22];
            strftime(formattedTime, sizeof(formattedTime),
                     "[%Y-%m-%d] %H:%M:%S", timeInfo);
            cout << formattedTime << endl;
            counter++;
            if ((counter % 3) == 0) {
                cout << "“This program has gone on for far too long. Type "
                        "Ctrl+C to abort this timer application.”"
                     << endl;
            }
            sleep(10);

            // Added for handling zombie process (child process already finished
            // but still remains in the processes list when you run ps -ax)
            int status;
            pid_t result = waitpid(pid, &status, WNOHANG);
            if (result == pid) {
                cout << "Child process (" << pid << ") already exited." << endl;
            };

            continue;
        }
    }

    return 0;
}