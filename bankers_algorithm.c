#include <fcntl.h>      // for O_* constants
#include <stdio.h>      // for printf
#include <stdlib.h>     // for atoi (parse int from string)
#include <unistd.h>     // for ftruncate
#include <stdbool.h>    // for bool type

// Modifiable constants
// instead of P0-P4, we will have P1-P5 and "P0" is reserved as a fake process to
// indicate the available resources
// TODO: read this from a CSV file
#define nProcesses 6
#define nKindsOfResource 3
unsigned short allocation[nProcesses][nKindsOfResource] = {
    {3, 3, 2},  // available resources
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};
const unsigned short max[nProcesses][nKindsOfResource] = {
    {0, 0, 0},
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};
#define available allocation[0]


void readFromStdin() {
    // open and read from stdin
    unsigned char buffer2[2];
    size_t bytesRead = fread(buffer2, sizeof(unsigned char), sizeof(buffer2), stdin);

    unsigned char nProcess = buffer2[0];
    unsigned char nKindsOfResources = buffer2[1];

    printf("Read %zu bytes.\n", bytesRead);
    printf("nProcess: %u\n", nProcess);
    printf("nKindsOfResources: %u\n", nKindsOfResources);
}

bool isInSafeState(unsigned short* safeSequence) {
    bool finish[nProcesses] = { false };
    // process 0 is not a real process, it's just a placeholder for available
    // resources, so we consider it finished
    finish[0] = true;

    unsigned short nFinished = 0;

    unsigned short i = 1;
    while (i < nProcesses) {
        if (finish[i]) {
            i++;
            continue;
        }

        bool canFinish = true;
        for (int r = 0; r < nKindsOfResource; r++) {
            if (max[i][r] - allocation[i][r] > available[r]) {
                canFinish = false;
                break;
            }
        }

        if (canFinish) {
            for (int r = 0; r < nKindsOfResource; r++) {
                available[r] += allocation[i][r];
            }
            safeSequence[nFinished] = i;
            finish[i] = true;
            nFinished++;
            i = 0;
        } else {
            i++;
        }
    }

    return nFinished == nProcesses-1;
}

int main(int argc, char *argv[]) {
    readFromStdin();

    unsigned short safeSequence[nProcesses-1] = { 0 };
    if (isInSafeState(safeSequence)) {
        printf("System is in safe state\n");
        printf("Safe sequence: ");
        for (int i = 0; i < nProcesses-1; i++) {
            printf("P%d", safeSequence[i]);
            if (i < nProcesses-2) {
                printf(" -> ");
            }
        }
    } else {
        printf("System is not in safe state\n");
    }

    return 0;
}
