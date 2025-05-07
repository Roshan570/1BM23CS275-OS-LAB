#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10

int main() {
    int n, m, i, j;

    int Allocation[MAX_P][MAX_R], Max[MAX_P][MAX_R], Need[MAX_P][MAX_R];
    int Available[MAX_R], Finish[MAX_P] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation matrix (%dx%d):\n", n, m);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &Allocation[i][j]);

    printf("Enter Max matrix (%dx%d):\n", n, m);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &Max[i][j]);

    printf("Enter Available resources (%d):\n", m);
    for (j = 0; j < m; j++)
        scanf("%d", &Available[j]);

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];

    printf("\nProcess\tAllocation\tMax\t\tNeed\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t", i);
        for (j = 0; j < m; j++)
            printf("%d ", Allocation[i][j]);
        printf("\t\t");
        for (j = 0; j < m; j++)
            printf("%d ", Max[i][j]);
        printf("\t\t");
        for (j = 0; j < m; j++)
            printf("%d ", Need[i][j]);
        printf("\n");
    }
    int count = 0;
    while (count < n) {
        bool found = false;
        for (i = 0; i < n; i++) {
            if (!Finish[i]) {
                bool canRun = true;
                for (j = 0; j < m; j++) {
                    if (Need[i][j] > Available[j]) {
                        canRun = false;
                        break;
                    }
                }
                if (canRun) {
                    for (j = 0; j < m; j++)
                        Available[j] += Allocation[i][j];
                    Finish[i] = 1;
                    found = true;
                    count++;
                }
            }
        }
        if (!found)
            break;
    }

    bool deadlock = false;
    printf("\nDeadlocked processes: ");
    for (i = 0; i < n; i++) {
        if (!Finish[i]) {
            printf("P%d ", i);
            deadlock = true;
        }
    }
    if (!deadlock)
        printf("None. No deadlock detected.\n");
    else
        printf("\nDeadlock detected among above processes.\n");

    return 0;
}

OUTPUT:
Enter number of processes: 3
Enter number of resources: 2
Enter Allocation matrix (3x2):
0 1
2 0
3 0
Enter Max matrix (3x2):
3 2
2 1
3 1
Enter Available resources (2):
0 0

Process Allocation      Max             Need
P0      0 1             3 2             3 1
P1      2 0             2 1             0 1
P2      3 0             3 1             0 1

Deadlocked processes: P0 P1 P2
Deadlock detected among above processes.
