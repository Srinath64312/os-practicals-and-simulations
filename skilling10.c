/*
 * Skilling Session 10: POSIX Threads (pthreads) and Mutex Synchronization
 * Demonstrates thread creation, joining, race condition prevention via mutex.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 4
#define INCREMENTS_PER_THREAD 100000

static int shared_counter = 0;
static pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *worker(void *arg) {
    long tid = (long)arg;
    for (int i = 0; i < INCREMENTS_PER_THREAD; i++) {
        pthread_mutex_lock(&counter_mutex);
        shared_counter++;
        pthread_mutex_unlock(&counter_mutex);
    }
    printf("[Thread %ld] Completed %d increments.\n", tid, INCREMENTS_PER_THREAD);
    return NULL;
}

int main(void) {
    pthread_t threads[NUM_THREADS];

    printf("=========================================================\n");
    printf("   OSSP Skilling Session 10: POSIX Threads & Mutex Sync  \n");
    printf("=========================================================\n");
    printf("Spawning %d threads with mutex-protected counter...\n\n", NUM_THREADS);

    for (long i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, worker, (void *)i) != 0) {
            perror("pthread_create failed");
            exit(EXIT_FAILURE);
        }
    }

    /* Wait for all threads to terminate */
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&counter_mutex);

    printf("\nExpected final counter value: %d\n", NUM_THREADS * INCREMENTS_PER_THREAD);
    printf("Actual final counter value  : %d\n", shared_counter);
    printf("Synchronization Status: %s\n",
           shared_counter == (NUM_THREADS * INCREMENTS_PER_THREAD) ? "PASSED (Zero Race Conditions)" : "FAILED");

    return 0;
}
