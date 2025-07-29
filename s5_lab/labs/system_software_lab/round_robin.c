#include <stdio.h>

int main() {
    int n, i, j, time = 0, tq, remain;
    int at[10], bt[10], rt[10];
    int wt[10], tat[10], completed[10] = {0};
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    remain = n;

    printf("Enter arrival times:\n");
    for(i = 0; i < n; i++) {
        printf("Arrival time of P%d: ", i);
        scanf("%d", &at[i]);
    }

    printf("Enter burst times:\n");
    for(i = 0; i < n; i++) {
        printf("Burst time of P%d: ", i);
        scanf("%d", &bt[i]);
        rt[i] = bt[i]; // Copy burst time to remaining time
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    printf("\nGantt Chart:\n");
    while(remain != 0) {
        int done = 1;
        for(i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0) {
                done = 0;
                if(rt[i] > tq) {
                    printf("P%d -> ", i);
                    time += tq;
                    rt[i] -= tq;
                } else {
                    printf("P%d -> ", i);
                    time += rt[i];
                    tat[i] = time - at[i];
                    wt[i] = tat[i] - bt[i];
                    rt[i] = 0;
                    completed[i] = 1;
                    remain--;
                }
            }
        }
        if(done) time++;
    }

    printf("\n\nProcess\tAT\tBT\tWT\tTAT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i, at[i], bt[i], wt[i], tat[i]);
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat / n);

    return 0;
}

