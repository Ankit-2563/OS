#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t room;
sem_t chopstick[5];

void *philosopher(void *num);
void eat(int phil);

int main()
{
    int i;
    int a[5];
    pthread_t tid[5];

    // Only 4 philosophers allowed in the room at once to avoid deadlock
    sem_init(&room, 0, 4);

    for (i = 0; i < 5; i++)
    {
        sem_init(&chopstick[i], 0, 1);
        a[i] = i;
    }

    for (i = 0; i < 5; i++)
    {
        pthread_create(&tid[i], NULL, philosopher, &a[i]);
    }

    for (i = 0; i < 5; i++)
    {
        pthread_join(tid[i], NULL);
    }

    return 0;
}

void *philosopher(void *num)
{
    int phil = *(int *)num;

    sem_wait(&room); // Enter room
    printf("Philosopher %d has entered the room\n", phil);

    sem_wait(&chopstick[phil]);           // Pick left chopstick
    sem_wait(&chopstick[(phil + 1) % 5]); // Pick right chopstick

    eat(phil); // Eating

    sleep(1); // Simulate eating time

    printf("Philosopher %d has finished eating\n", phil);

    sem_post(&chopstick[(phil + 1) % 5]); // Put down right chopstick
    sem_post(&chopstick[phil]);           // Put down left chopstick

    sem_post(&room); // Leave room

    pthread_exit(NULL);
}

void eat(int phil)
{
    printf("Philosopher %d is eating\n", phil);
}
