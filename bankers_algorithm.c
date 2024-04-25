#include <fcntl.h>      // for O_* constants
#include <stdio.h>      // for printf
#include <stdlib.h>     // for exit
#include <unistd.h>     // for ftruncate
#include <stdbool.h>    // for bool type

// Modifiable constants
// instead of P0-P4, we will have P1-P5 and "P0" is reserved as a fake process to
// indicate the available resources
#define available allocation[0]


void inputTooShort(char* input) {
    printf("ERROR: Input too short: ");
    printf(input);
    printf("\n");
    exit(2);
}

int main() {
    //
    // read input
    //
    unsigned char buffer[2];
    size_t bytesRead = fread(buffer, sizeof(unsigned char), sizeof(buffer), stdin);

    if (bytesRead < 2) {
        inputTooShort("Header must contain 2 bytes: Number of processes and number of kinds of resources.");
    }

    unsigned char nProcesses = buffer[0];
    unsigned char nKindsOfResources = buffer[1];

    printf("nProcesses: %u\n", nProcesses);
    printf("nKindsOfResources: %u\n", nKindsOfResources);

    unsigned char allocation[nProcesses][nKindsOfResources];
    bytesRead = fread(allocation, sizeof(unsigned char), sizeof(allocation), stdin);
    if (bytesRead < nProcesses * nKindsOfResources) {
        inputTooShort("Allocation matrix size must equal the number of processes times the number of kinds of resources.");
    }

    unsigned char max[nProcesses][nKindsOfResources];
    bytesRead = fread(max, sizeof(unsigned char), sizeof(max), stdin);
    if (bytesRead < nProcesses * nKindsOfResources) {
        inputTooShort("Max matrix size must equal the number of processes times the number of kinds of resources.");
    }

    //
    // check if the system is in a safe state
    //
    unsigned short safeSequence[nProcesses-1] = { };  // TODO: check this is all 0
    bool finish[nProcesses] = { };  // TODO: check this is all false
    // process 0 is not a real process, it's just a placeholder for available
    // resources, so we consider it finished
    finish[0] = true;

    unsigned char nFinished = 0;

    unsigned char i = 1;
    while (i < nProcesses) {
        if (finish[i]) {
            i++;
            continue;
        }

        bool canFinish = true;
        for (int r = 0; r < nKindsOfResources; r++) {
            if (max[i][r] - allocation[i][r] > available[r]) {
                canFinish = false;
                break;
            }
        }

        if (canFinish) {
            for (int r = 0; r < nKindsOfResources; r++) {
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

    //
    // output results
    //
    if (nFinished == nProcesses-1) {
        printf("System is in safe state\n");
        printf("Safe sequence: ");
    } else {
        printf("System is not in safe state\n");
        printf("Sequence: ");
    }
    for (int i = 0; i < nProcesses-1; i++) {
        if (safeSequence[i] == 0) {
            break;
        }
        printf("P%d", safeSequence[i]);
        if (i < nProcesses-2) {
            printf(" -> ");
        }
    }
    printf("\n");

    return 0;
}
