#include <cstring>
#include <fstream>
#include <iostream>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
using namespace std;

int SHM_KEY_A = 1234;
int SHM_KEY_B = 5678;
int SEM_KEY = 2468;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0]
             << " <textfile> <shared memory size in bytes>\n";
        return 1;
    }

    // Ensure existing shared memory is cleared before starting copy
    int existing_shmidA = shmget(SHM_KEY_A, 0, 0);
    if (existing_shmidA != -1) {
        shmctl(existing_shmidA, IPC_RMID, NULL);
    }

    int existing_shmidB = shmget(SHM_KEY_B, 0, 0);
    if (existing_shmidB != -1) {
        shmctl(existing_shmidB, IPC_RMID, NULL);
    }

    ifstream input(argv[1], ios::binary); // Open input file
    int shmSize = stoi(argv[2]);          // Get shared memory size

    // Get Shared Memory
    int shmidA = shmget(SHM_KEY_A, shmSize, IPC_CREAT | 0666);
    int shmidB = shmget(SHM_KEY_B, 2, IPC_CREAT | 0666);

    // Get Sempahore
    int semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);

    // Set Semaphore to 1
    semctl(semid, 0, SETVAL, 1);

    // shmData
    // contains the data being read from input file
    char *shmData = (char *)shmat(shmidA, NULL, 0); // Attach shmData

    // shmStatus
    // contains the status of the transfer <Status> <n bytes to write>
    // Status of Transfer:
    // First byte:
    // 1 - writing (process has read data)
    // 2 - reading (process has written data)
    // 3 - done
    // 0 - not started
    // Second byte contains the number of bytes to write to the new file
    char *shmStatus = (char *)shmat(shmidB, NULL, 0); // Attach shmStatus

    shmStatus[0] = 0; // Set initial status to 0
    shmStatus[1] = 0; // Set initial bytes transferred to 0

    // Define Semaphore Operations

    struct sembuf lock[1]; // Decrement Semaphore by 1
    lock[0].sem_num = 0;
    lock[0].sem_op = -1;
    lock[0].sem_flg = SEM_UNDO;

    struct sembuf unlock[1]; // Increment Semaphore by 1
    unlock[0].sem_num = 0;
    unlock[0].sem_op = 1;
    unlock[0].sem_flg = SEM_UNDO;

    bool done = false;
    while (!done) {
        sleep(1); //Give consumer chance to run

        if (semop(semid, lock, 1) == -1) {
            perror("Sempahore Lock");
            break;
        }

        // If current status is reading or not started
        if (shmStatus[0] == 2 || shmStatus[0] == 0) {

            // Save shmSize bytes of input file to shmData
            input.read(shmData, shmSize); 
            streamsize bytesRead = input.gcount(); 

            if (bytesRead > 0) {
                // If bytesRead is less than buffer size, pad out with '\0'
                if (bytesRead < shmSize) {
                    shmData[bytesRead] = '\0';
                }
                shmStatus[1] = bytesRead;
                shmStatus[0] = 1; //writing

            } else {
                // If no bytes read, end process
                shmStatus[0] = 3;
                done = true;
            }
        }

        if (semop(semid, unlock, 1) == -1) {
            perror("Sempahore Unlock Fail");
            break;
        }
    }

    // Detach Shared Memory
    shmdt(shmData);
    shmdt(shmStatus);
    input.close();
    
    return 0;
}