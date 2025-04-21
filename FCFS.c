#include <stdio.h>
#define MAX_PROCESSES 100 // Define a constant for the maximum number of processes

typedef struct
{
    int processID;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
} Process;

void calculateTimes(Process processes[], int n)
{
    int currentTime = 0;

    for (int i = 0; i < n; i++)
    {
        if (currentTime < processes[i].arrivalTime)
        {
            currentTime = processes[i].arrivalTime;
        }

        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        currentTime = processes[i].completionTime;
    }
}

void printTable(Process processes[], int n)
{
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               processes[i].processID,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].completionTime,
               processes[i].turnaroundTime,
               processes[i].waitingTime);
    }
}

int main()
{
    int n;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &n);

    if (n > MAX_PROCESSES)
    {
        printf("Error: Number of processes exceeds the maximum limit of %d.\n", MAX_PROCESSES);
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        processes[i].processID = i + 1;
        printf("Enter arrival time and burst time for process P%d: ", i + 1);
        scanf("%d%d", &processes[i].arrivalTime, &processes[i].burstTime);
    }

    // Optional: Sort processes by arrival time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (processes[i].arrivalTime > processes[j].arrivalTime)
            {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    calculateTimes(processes, n);
    printTable(processes, n);

    return 0;
}
