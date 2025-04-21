#include <stdio.h>
#define MAX 25

int main()
{
    int frag[MAX], b[MAX], f[MAX];
    int bf[MAX] = {0}; // Array to keep track of allocated blocks
    int nb, nf, i, j, temp, lowest, bestFitIndex;

    // Input number of blocks and files
    printf("\nMemory Management Scheme - Best Fit\n");
    printf("Enter the number of blocks: ");
    scanf("%d", &nb);
    printf("Enter the number of files: ");
    scanf("%d", &nf);

    // Input block sizes
    printf("\nEnter the size of the blocks:\n");
    for (i = 0; i < nb; i++)
    {
        printf("Block %d: ", i + 1);
        scanf("%d", &b[i]);
    }

    // Input file sizes
    printf("\nEnter the size of the files:\n");
    for (i = 0; i < nf; i++)
    {
        printf("File %d: ", i + 1);
        scanf("%d", &f[i]);
    }

    // Best Fit Allocation
    for (i = 0; i < nf; i++)
    {
        lowest = 10000; // Reset the lowest fragment size
        bestFitIndex = -1;

        for (j = 0; j < nb; j++)
        {
            if (bf[j] != 1) // If block is not allocated
            {
                temp = b[j] - f[i]; // Calculate fragment size

                if (temp >= 0 && temp < lowest) // If it fits and is the smallest so far
                {
                    bestFitIndex = j;
                    lowest = temp;
                }
            }
        }

        // If a suitable block is found, allocate it
        if (bestFitIndex != -1)
        {
            bf[bestFitIndex] = 1; // Mark block as allocated
            frag[i] = lowest;     // Store the fragment size
        }
        else
        {
            frag[i] = -1; // If no suitable block, mark it as -1
        }
    }

    // Display the allocation details
    printf("\nFile No\tFile Size\tBlock No\tBlock Size\tFragment\n");
    for (i = 0; i < nf; i++)
    {
        if (frag[i] != -1) // If file was allocated
        {
            printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, f[i], bestFitIndex + 1, b[bestFitIndex], frag[i]);
        }
        else
        {
            printf("%d\t\t%d\t\tNot Allocated\n", i + 1, f[i]);
        }
    }
}
