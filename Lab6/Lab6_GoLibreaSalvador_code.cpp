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
        int myXclock = execl("/usr/bin/xclock", "myXclock", NULL);
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
                cout << "\"This program has gone on for far too long. Type Ctrl+C to abort this timer application.\""
                     << endl;
            }
            sleep(10);
            continue;
        }
    }

    return 0;
}