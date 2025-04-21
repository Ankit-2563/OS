#include <stdio.h>

int main()
{
    int at[10], bt[10], rt[10]; // Arrival, Burst, and Remaining time
    int n, time = 0, remain = 0;
    int smallest = 0, endTime;
    int sum_wait = 0, sum_turnaround = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input arrival and burst times
    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time for Process P%d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter burst time for Process P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i]; // Remaining time initialized as burst time
    }

    printf("\nProcess\t| Turnaround Time | Waiting Time\n");

    while (remain != n)
    {
        smallest = -1;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && rt[i] > 0)
            {
                if (smallest == -1 || rt[i] < rt[smallest])
                    smallest = i;
            }
        }

        if (smallest == -1)
        {
            time++; // No process has arrived yet
            continue;
        }

        rt[smallest]--;
        time++;

        if (rt[smallest] == 0)
        {
            remain++;
            endTime = time;
            int turnaround = endTime - at[smallest];
            int waiting = turnaround - bt[smallest];

            printf("P[%d]\t|\t%d\t|\t%d\n", smallest + 1, turnaround, waiting);

            sum_wait += waiting;
            sum_turnaround += turnaround;
        }
    }

    printf("\nAverage Waiting Time: %.2f\n", sum_wait * 1.0 / n);
    printf("Average Turnaround Time: %.2f\n", sum_turnaround * 1.0 / n);

    return 0;
}
