#include <stdio.h>    // for printf
#include <stdlib.h>   // for exit
#include <stdbool.h>  // for bool type

// instead of P0-P4, we will have P1-P5 and "P0" is reserved as a fake process
// to indicate the available resources
#define available allocation[0]


void inputTooShort(char* input) {
    fprintf(stderr, "ERROR: Input too short: ");
    fprintf(stderr, input);
    fprintf(stderr, "\n");
    exit(2);
}

int main(int argc, char* argv[]) {
    bool debug = false;
    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'v') {
        debug = true;
    }

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

    if (debug) {
        fprintf(stderr, "nProcesses: %u\n", nProcesses);
        fprintf(stderr, "nKindsOfResources: %u\n", nKindsOfResources);
    }

    if (nProcesses < 1) {
        fprintf(stderr, "ERROR: Number of processes must be at least 1.\n");
        exit(3);
    }

    unsigned char allocation[nProcesses][nKindsOfResources];
    bytesRead = fread(allocation, sizeof(unsigned char), sizeof(allocation), stdin);
    if (debug) {
        fprintf(stderr, "Allocation matrix:\n");
        for (int i = 0; i < nProcesses; i++) {
            for (int j = 0; j < nKindsOfResources; j++) {
                fprintf(stderr, "%u ", allocation[i][j]);
            }
            fprintf(stderr, "\n");
        }
    }
    if (bytesRead < nProcesses * nKindsOfResources) {
        inputTooShort("Allocation matrix size must equal the number of processes times the number of kinds of resources.");
    }

    unsigned char max[nProcesses][nKindsOfResources];
    bytesRead = fread(max, sizeof(unsigned char), sizeof(max), stdin);
    if (debug) {
        fprintf(stderr, "Max matrix:\n");
        for (int i = 0; i < nProcesses; i++) {
            for (int j = 0; j < nKindsOfResources; j++) {
                fprintf(stderr, "%u ", max[i][j]);
            }
            fprintf(stderr, "\n");
        }
    }
    if (bytesRead < nProcesses * nKindsOfResources) {
        inputTooShort("Max matrix size must equal the number of processes times the number of kinds of resources.");
    }

    //
    // check if the system is in a safe state
    //
    unsigned short safeSequence[nProcesses-1] = {};
    bool finish[nProcesses] = {};
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
        printf("System is in a safe state.\n");
        printf("Safe sequence: ");
    } else {
        printf("System is not in a safe state.\n");
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

    if (nFinished == nProcesses-1) {
        return 0;
    } else {
        return 1;
    }
}
