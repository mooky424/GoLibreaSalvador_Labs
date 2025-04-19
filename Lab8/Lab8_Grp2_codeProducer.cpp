#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

key_t SHM_KEY_A = 1234;
key_t SHM_KEY_B = 5678;
key_t SEM_KEY = 2468;

struct shmStatus {
    char status;
    int count;
};

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

    int shmSize = stoi(argv[2]); // Get shared memory size

    int input = open(argv[1], O_RDONLY);
    if (input == -1) {
        perror("Input File Error");
        return -1;
    }

    // Get Shared Memory
    int shmidA = shmget(SHM_KEY_A, shmSize, IPC_CREAT | 0666);
    if (shmidA == -1) {
        perror("Shared Memory A Error");
        return -1;
    }
    int shmidB = shmget(SHM_KEY_B, sizeof(shmStatus), IPC_CREAT | 0666);
    if (shmidB == -1) {
        perror("Shared Memory B Error");
        return -1;
    }

    // Get Sempahore
    int semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("Semaphore Creation Error");
        return -1;
    }

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
    shmStatus *shmStat = (shmStatus *)shmat(shmidB, NULL, 0); // Attach shmStatus

    shmStat->status = 0; // Set initial status to 0
    shmStat->count = 0; // Set initial bytes transferred to 0

    // Define Semaphore Operations

    struct sembuf lock[1]; // Decrement Semaphore by 1
    lock[0].sem_num = 0;
    lock[0].sem_op = -1;
    lock[0].sem_flg = 0;

    struct sembuf unlock[1]; // Increment Semaphore by 1
    unlock[0].sem_num = 0;
    unlock[0].sem_op = 1;
    unlock[0].sem_flg = 0;

    bool done = false;
    while (!done) {
        sleep(1);

        if (semop(semid, lock, 1) == -1) {
            perror("Producer Semaphore Lock");
            break;
        }

        if (shmStat->status == 2 || shmStat->status == 0) {
            ssize_t bytesRead = read(input, shmData, shmSize);

            if (bytesRead > 0) {
                shmStat->count = bytesRead;
                shmStat->status = 1;        // Writing status
            } else if (bytesRead == 0) { // EOF
                shmStat->status = 3;
                done = true;
            } else {
                perror("Read error");
                break;
            }
        }

        if (semop(semid, unlock, 1) == -1) {
            perror("Producer Semaphore Unlock");
            break;
        }
    }

    // Detach Shared Memory
    shmdt(shmData);
    shmdt(shmStat);
    close(input);

    return 0;
}