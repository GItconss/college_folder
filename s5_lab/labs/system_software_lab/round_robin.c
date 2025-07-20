#include <stdio.h>

int main()
{
    int n, time_quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], burst_time[n], remaining_time[n], waiting_time[n], turnaround_time[n];
    float total_waiting_time = 0, total_turnaround_time = 0;

    // Input burst times
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        printf("Enter burst time for Process %d: ", pid[i]);
        scanf("%d", &burst_time[i]);
        remaining_time[i] = burst_time[i];
        waiting_time[i] = 0;
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    int time = 0, done;

    do
    {
        done = 1;
        for (int i = 0; i < n; i++)
        {
            if (remaining_time[i] > 0)
            {
                done = 0;

                if (remaining_time[i] > time_quantum)
                {
                    time += time_quantum;
                    remaining_time[i] -= time_quantum;
                }
                else
                {
                    time += remaining_time[i];
                    waiting_time[i] = time - burst_time[i];
                    remaining_time[i] = 0;
                }
            }
        }
    } while (!done);

    // Calculate turnaround time
    for (int i = 0; i < n; i++)
    {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    // Display table
    printf("\nPID\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\n", pid[i], burst_time[i], waiting_time[i], turnaround_time[i]);
    }

    // Display averages
    printf("\nAverage Waiting Time = %.2f", total_waiting_time / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_turnaround_time / n);

    return 0;
}
