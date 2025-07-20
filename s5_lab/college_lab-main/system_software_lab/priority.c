#include <stdio.h>
int main()
{
    int n, i, j, temp;
    int bt[25], pid[25], tat[25], wt[25], rt[25], priority[25];
    float t_tat = 0.0, t_wt = 0.0;

    printf("enter the size : ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("enter the brust time p %d=", i + 1);
        scanf("%d", &bt[i]);
        printf("enter the proirity :");
        scanf("%d", &priority[i]);
        pid[i] = i + 1;
    }
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (priority[j] < priority[i])
            {
                temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    wt[0] = 0;
    tat[0] = bt[0];
    for (i = 1; i < n; i++)
    {
        wt[i] = bt[i - 1] + wt[i - 1];
        tat[i] = bt[i] + wt[i];
    }

    for (i = 0; i < n; i++)
    {

        t_tat += tat[i];
        t_wt += wt[i];
    }
    printf("p_id\tprority\tbrust_time\ttturnaround_t\twaiting_t\\n");
    for (i = 0; i < n; i++)
    {
        printf("%4d\t%7d\t%%9d\t%11d\t%10d\t\n", pid[i], priority[i], bt[i], tat[i], wt[i]);
    }
    printf(" Avg turnaround time = %.2f", t_tat / n);
    printf(" Avg waiting time = %.2f", t_wt / n);
}