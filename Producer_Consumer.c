#include <stdio.h>

#define BUFFER_SIZE 3

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int count = 0;

int mutex = 1;
int full = 0;
int empty = BUFFER_SIZE;

void wait(int *s);
void signal(int *s);
void producer();
void consumer();

int main()
{
    int choice;

    printf("Producer-Consumer Problem (Using Semaphores)\n");
    printf("1. Produce\n2. Consume\n3. Exit\n");

    while (1)
    {
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (empty > 0 && mutex == 1)
            {
                producer();
            }
            else
            {
                printf("Buffer is full! Producer is waiting...\n");
            }
            break;
        case 2:
            if (full > 0 && mutex == 1)
            {
                consumer();
            }
            else
            {
                printf("Buffer is empty! Consumer is waiting...\n");
            }
            break;
        case 3:
            return 0;
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
}

/* Producer function */
void producer()
{
    int item;
    printf("Enter item to produce: ");
    scanf("%d", &item);

    wait(&mutex);
    wait(&empty);

    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    count++;

    printf("Produced: %d\n", item);

    signal(&full);
    signal(&mutex);
}

/* Consumer function */
void consumer()
{
    int item;

    wait(&mutex);
    wait(&full);

    item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    count--;

    printf("Consumed: %d\n", item);

    signal(&empty);
    signal(&mutex);
}

/* Wait (P) operation */
void wait(int *s)
{
    while (*s <= 0)
        ; // Busy wait
    (*s)--;
}

/* Signal (V) operation */
void signal(int *s)
{
    (*s)++;
}
