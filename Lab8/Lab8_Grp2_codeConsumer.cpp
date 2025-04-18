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
             << " <textfileCopy> <shared memory size in bytes>\n";
        return 1;
    }

    ofstream output(argv[1], ios::binary); // Open output file
    int shmSize = stoi(argv[2]);           // Get shared memory sizse

    // Get shared memory segments
    int shmidA = shmget(SHM_KEY_A, shmSize, 0666);
    int shmidB = shmget(SHM_KEY_B, 2, 0666);
    
    //Get Semaphore
    int semid = semget(SEM_KEY, 1, 0666);

    // shmData
    // contains the data being read from input file
    char *shmData = (char *)shmat(shmidA, NULL, 0); //attach shmData

    // shmStatus
    // contains the status of the transfer <Status> <n bytes to write>
    // Status of Transfer:
    // First byte:
    // 1 - writing
    // 2 - reading
    // 3 - done
    // 0 - not started
    // Second byte contains the number of bytes to write to the new file
    char *shmStatus = (char *)shmat(shmidB, NULL, 0); // attach shmStatus

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
        sleep(1); // Give producer chance to run

        if (semop(semid, lock, 1) == -1) {
            perror("Sempahoer Lock");
            break;
        }

        // If current status is done
        if (shmStatus[0] == 3) {
            done = true;

        // If current status is writing
        } else if (shmStatus[0] == 1) {

            // Get no. of bytes to write to file
            int bytesToWrite = static_cast<unsigned char>(shmStatus[1]);
            
            // Write data to file
            output.write(shmData, bytesToWrite);
            if (!output) {
                perror("File write failed");
                break;
            }
            output.flush();
            shmStatus[0] = 2; // reading
        }

        // Unlock semaphore
        if (semop(semid, unlock, 1) == -1) {
            perror("Semaphore Unlock Fail");
            break;
        }
    }

    // Detach shared memory
    shmdt(shmData);
    shmdt(shmStatus);
    output.close();

    // Memory/Semaphore Cleanup
    shmctl(shmidA, IPC_RMID, NULL);
    shmctl(shmidB, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);

    return 0;
}