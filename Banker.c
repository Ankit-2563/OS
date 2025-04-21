#include <stdio.h>

int main()
{
    int n, m, i, j, k;
    int f[10], ans[10], ind = 0; // f[] to track finished processes
    int alloc[10][5], max[10][5], avail[5], need[10][5];

    // Input number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    // Input allocation matrix
    printf("Enter allocation matrix alloc[%d][%d]:\n", n, m);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input maximum matrix
    printf("Enter maximum matrix max[%d][%d]:\n", n, m);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    // Input available resources matrix
    printf("Enter available resources matrix avail[%d]:\n", m);
    for (i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
    }

    // Initialize finished processes array to 0 (not finished)
    for (k = 0; k < n; k++)
    {
        f[k] = 0;
    }

    // Calculate the need matrix
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Banker's Algorithm to find safe sequence
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            if (f[i] == 0)
            {
                int flag = 0;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                // If the process can be safely completed
                if (flag == 0)
                {
                    ans[ind++] = i;
                    for (j = 0; j < m; j++)
                    {
                        avail[j] += alloc[i][j]; // Release the resources
                    }
                    f[i] = 1; // Mark the process as finished
                }
            }
        }
    }

    // Check if the system is in a safe state
    int flag = 1;
    for (i = 0; i < n; i++)
    {
        if (f[i] == 0)
        {
            flag = 0;
            printf("The following system is not safe\n");
            break;
        }
    }

    // If system is in a safe state, print the safe sequence
    if (flag == 1)
    {
        printf("Following is the SAFE Sequence:\n");
        for (i = 0; i < n - 1; i++)
        {
            printf("P%d -> ", ans[i]);
        }
        printf("P%d\n", ans[n - 1]);
    }

    return 0;
}
