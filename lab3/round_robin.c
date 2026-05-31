#include <stdio.h>

#define MAX 20

int main() {
    int n, i, time = 0, remain, quantum;
    int at[MAX], bt[MAX], rt[MAX];
    int ct[MAX], tat[MAX], wt[MAX], response[MAX];
    int first_exec[MAX];

    // Gantt chart arrays
    int gantt[MAX * 10], gtime[MAX * 10];
    int gindex = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    remain = n;

    // Input
    for(i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];        // remaining time
        first_exec[i] = -1;   // to track first execution
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    gtime[0] = 0;

    while(remain > 0) {
        int executed = 0;

        for(i = 0; i < n; i++) {
            if(rt[i] > 0 && at[i] <= time) {
                executed = 1;

                // Record first response time
                if(first_exec[i] == -1) {
                    first_exec[i] = time;
                    response[i] = first_exec[i] - at[i];
                }

                gantt[gindex++] = i;

                if(rt[i] > quantum) {
                    time += quantum;
                    rt[i] -= quantum;
                } else {
                    time += rt[i];
                    rt[i] = 0;

                    ct[i] = time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];

                    remain--;
                }

                gtime[gindex] = time;
            }
        }

        // CPU idle
        if(!executed) {
            time++;
            gtime[gindex] = time;
        }
    }

    // Display table
    float totalTAT = 0, totalWT = 0, totalRT = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i], response[i]);

        totalTAT += tat[i];
        totalWT += wt[i];
        totalRT += response[i];
    }

    printf("\nAverage Turnaround Time = %.2f", totalTAT / n);
    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Response Time = %.2f\n", totalRT / n);

    // Gantt Chart
    printf("\nGantt Chart:\n");

    for(i = 0; i < gindex; i++)
        printf("--------");
    printf("\n|");

    for(i = 0; i < gindex; i++)
        printf(" P%d |", gantt[i] + 1);

    printf("\n");

    for(i = 0; i < gindex; i++)
        printf("--------");

    printf("\n");

    for(i = 0; i <= gindex; i++)
        printf("%d\t", gtime[i]);

    printf("\n");

    return 0;
}
