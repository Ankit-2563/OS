#include <stdio.h>

int main()
{
    int n, i, time = 0, remaining, tq;
    int at[10], bt[10], rt[10]; // at: arrival time, bt: burst time, rt: remaining time
    int wt = 0, tat = 0;        // wt: total waiting time, tat: total turnaround time
    float avg_wt, avg_tat;

    printf("Enter total number of processes (max 10): ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        rt[i] = bt[i]; // Initialize remaining time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    printf("\nProcess\tBurst\tTAT\tWaiting\n");

    remaining = n;
    int current = 0, flag;

    while (remaining != 0)
    {
        flag = 0;

        if (rt[current] > 0 && at[current] <= time)
        {
            flag = 1;

            if (rt[current] <= tq)
            {
                time += rt[current];
                rt[current] = 0;

                int turnaround = time - at[current];
                int waiting = turnaround - bt[current];

                printf("P%d\t%d\t%d\t%d\n", current + 1, bt[current], turnaround, waiting);

                wt += waiting;
                tat += turnaround;
                remaining--;
            }
            else
            {
                rt[current] -= tq;
                time += tq;
            }
        }

        // Move to next process
        current = (current + 1) % n;

        // If no process was executed in this full cycle, jump time forward
        if (!flag)
        {
            int earliest = -1;
            for (i = 0; i < n; i++)
            {
                if (rt[i] > 0)
                {
                    if (earliest == -1 || at[i] < at[earliest])
                        earliest = i;
                }
            }
            if (earliest != -1 && at[earliest] > time)
            {
                time = at[earliest];
            }
        }
    }

    avg_wt = (float)wt / n;
    avg_tat = (float)tat / n;

    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);

    return 0;
}
