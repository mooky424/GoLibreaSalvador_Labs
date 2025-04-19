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
    char status; // Status of transfer
    int count;   // Number of bytes to write
};

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0]
             << " <textfileCopy> <shared memory size in bytes>\n";
        return -1;
    }

    int output = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (output == -1) {
        perror("Output File Error");
        return -1;
    }

    int shmSize = stoi(argv[2]); // Get shared memory sizse

    // Get Shared Memory
    int shmidA = shmget(SHM_KEY_A, shmSize, IPC_CREAT | 0666);
    if (shmidA == -1) {
        perror("Shared Memory A Error");
        return -1;
    }
    int shmidB = shmget(SHM_KEY_B, 2, IPC_CREAT | 0666);
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

    // shmData
    // contains the data being read from input file
    char *shmData = (char *)shmat(shmidA, NULL, 0); // attach shmData

    // shmStat
    // contains the status of the transfer <Status> <n bytes to write>
    // Status of Transfer:
    // First byte:
    // 1 - writing
    // 2 - reading
    // 3 - done
    // 0 - not started
    // Second byte contains the number of bytes to write to the new file
    shmStatus *shmStat = (shmStatus *)shmat(shmidB, NULL, 0); // attach shmStat

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
            perror("Consumer Semaphore Lock");
            break;
        }

        if (shmStat->status == 3) {
            done = true;
        } else if (shmStat->status == 1) {
            int bytesToWrite = static_cast<unsigned int>(shmStat->count);
            ssize_t written = write(output, shmData, bytesToWrite);

            if (written != bytesToWrite) {
                perror("Write error");
            }
            shmStat->status = 2; // Reading status
        }

        if (semop(semid, unlock, 1) == -1) {
            perror("Consumer Semaphore Unlock");
            break;
        }
    }

    // Detach shared memory
    shmdt(shmData);
    shmdt(shmStat);
    close(output);

    // Memory/Semaphore Cleanup
    shmctl(shmidA, IPC_RMID, NULL);
    shmctl(shmidB, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);

    return 0;
}