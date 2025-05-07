#include <stdio.h>

#define MAX_PROCESS 10
#define MAX_RESOURCE 10

int isSafe(int avail[], int max[][MAX_RESOURCE], int allot[][MAX_RESOURCE], int need[][MAX_RESOURCE], int processCount, int resourceCount) {
    int work[MAX_RESOURCE], finish[MAX_PROCESS] = {0}, safeSeq[MAX_PROCESS], count = 0;

    for (int i = 0; i < resourceCount; i++) work[i] = avail[i];

    while (count < processCount) {
        int found = 0;
        for (int p = 0; p < processCount; p++) {
            if (!finish[p]) {
                int canFinish = 1;
                for (int r = 0; r < resourceCount; r++) {
                    if (need[p][r] > work[r]) {
                        canFinish = 0;
                        break;
                    }
                }
                if (canFinish) {
                    for (int r = 0; r < resourceCount; r++) work[r] += allot[p][r];
                    finish[p] = 1;
                    safeSeq[count++] = p;
                    found = 1;
                    break;
                }
            }
        }
        if (!found) return 0;
    }

    printf("Safe sequence: ");
    for (int i = 0; i < processCount; i++) printf("P%d ", safeSeq[i]);
    printf("\n");
    return 1;
}

int main() {
    int processCount, resourceCount;

    printf("Enter the number of processes: ");
    scanf("%d", &processCount);
    printf("Enter the number of resources: ");
    scanf("%d", &resourceCount);

    int avail[MAX_RESOURCE], max[MAX_PROCESS][MAX_RESOURCE], allot[MAX_PROCESS][MAX_RESOURCE], need[MAX_PROCESS][MAX_RESOURCE];

    printf("\nEnter available resources: ");
    for (int i = 0; i < resourceCount; i++) scanf("%d", &avail[i]);

    printf("\nEnter maximum demand for each process: ");
    for (int i = 0; i < processCount; i++)
        for (int j = 0; j < resourceCount; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter allocated resources for each process: ");
    for (int i = 0; i < processCount; i++)
        for (int j = 0; j < resourceCount; j++)
            scanf("%d", &allot[i][j]);

    for (int i = 0; i < processCount; i++)
        for (int j = 0; j < resourceCount; j++)
            need[i][j] = max[i][j] - allot[i][j];

    if (!isSafe(avail, max, allot, need, processCount, resourceCount)) {
        printf("The system is in a deadlock state.\n");
    }

    return 0;
}

OUTPUT:
Enter the number of processes: 2
Enter the number of resources: 3

Enter available resources: 3 3 2

Enter maximum demand for each process: 7 5 3
3 2 2

Enter allocated resources for each process: 0 1 0
2 0 0
The system is in a deadlock state.
