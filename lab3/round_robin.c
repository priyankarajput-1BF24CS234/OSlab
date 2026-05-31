#include <stdio.h>

int main() {
    int n, tq;
    int at[20], bt[20], rem_bt[20];
    int ct[20], tat[20], wt[20], rt[20];
    int completed = 0, time = 0;

    float avg_wt = 0, avg_tat = 0, avg_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    printf("Enter Arrival Time and Burst Time:\n");

    for(int i = 0; i < n; i++) {
        printf("P%d AT: ", i + 1);
        scanf("%d", &at[i]);

        printf("P%d BT: ", i + 1);
        scanf("%d", &bt[i]);

        rem_bt[i] = bt[i];
        rt[i] = -1;
    }

    while(completed < n) {

        int found = 0;

        for(int i = 0; i < n; i++) {

            if(at[i] <= time && rem_bt[i] > 0) {

                found = 1;

                if(rt[i] == -1)
                    rt[i] = time - at[i];

                if(rem_bt[i] > tq) {
                    time += tq;
                    rem_bt[i] -= tq;
                }
                else {
                    time += rem_bt[i];

                    ct[i] = time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];

                    avg_wt += wt[i];
                    avg_tat += tat[i];
                    avg_rt += rt[i];

                    rem_bt[i] = 0;
                    completed++;
                }
            }
        }

        if(!found)
            time++;
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i],
               tat[i], wt[i], rt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f", avg_tat / n);
    printf("\nAverage Response Time = %.2f\n", avg_rt / n);

    return 0;
}
