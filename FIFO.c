#include <stdio.h>

int main()
{
    int incomingStream[20];
    int pageFaults = 0;
    int frames;
    int i, m, n, s, pages;

    // Input number of frames and pages
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    printf("Enter number of pages: ");
    scanf("%d", &pages);
    printf("Enter page numbers: ");

    // Input the page numbers
    for (i = 0; i < pages; i++)
    {
        scanf("%d", &incomingStream[i]);
    }

    // Print header for page and frames
    printf("\nPage Nos.\t Frame 1\t Frame 2\t Frame 3\n");

    int temp[frames];            // Array for storing frames
    for (m = 0; m < frames; m++) // Initialize frames to -1 (empty)
    {
        temp[m] = -1;
    }

    int front = 0; // Variable to track FIFO

    for (m = 0; m < pages; m++) // Iterate through all pages
    {
        s = 0;
        // Check if the current page is already in one of the frames
        for (n = 0; n < frames; n++)
        {
            if (incomingStream[m] == temp[n])
            {
                s++; // Page is already in memory
                pageFaults--;
            }
        }

        pageFaults++; // Increment page faults as a new page is being processed

        // If the page is not found in memory, replace the oldest page (FIFO)
        if (s == 0)
        {
            temp[front] = incomingStream[m]; // Replace the oldest page in FIFO
            front = (front + 1) % frames;    // Move the pointer to the next frame
        }

        // Print the page numbers and frame contents
        printf("\n%d\t\t", incomingStream[m]);
        for (n = 0; n < frames; n++)
        {
            if (temp[n] != -1)
                printf("%d\t\t", temp[n]);
            else
                printf("-\t\t");
        }
    }

    // Output the total number of page faults
    printf("\nTotal Page Faults:\t%d\n", pageFaults);
    return 0;
}
