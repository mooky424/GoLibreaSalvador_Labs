#include <iostream>
#include <unistd.h>
#include <ctime>
using namespace std;

int main() {

  pid_t pid = fork();

  if ( pid < 0 ) {
    cout << "Failed fork" << endl;
    return -1;
  }
  
  if ( pid == 0 ) {
    cout << "Child Process Running: " << getpid() << ", Parent Process: " << getppid() << endl;
    int myXclock = execl("/opt/X11/bin/xclock", "myXclock", NULL);
    cout << "Failed executing xclock" << endl;
    return -1;
  }
  else {
    cout << "Parent Process Running: " << getpid() << endl;
    int printCounter = 0;
    while(true) {
      time_t timestamp = time(NULL);
      struct tm* timeInfo = localtime(&timestamp);
      char formattedTime[22];
      strftime(formattedTime, 22, "[%Y-%m-%d] %H:%M:%S", timeInfo);
      cout << formattedTime << endl;
      printCounter++;
      if ( (printCounter % 3) == 0) {
        cout << "“This program has gone on for far too long. Type Ctrl+C to abort this timer application.”" << endl;
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