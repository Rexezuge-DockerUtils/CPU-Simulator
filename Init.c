#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

/* Duration definitions (in seconds) */
#define BUSY_DURATION_SECONDS   (10 * 60)      /* 10 minutes */
#define SLEEP_DURATION_SECONDS  (10 * 60 * 60) /* 10 hours */

/*
 * Perform a busy loop for the specified duration.
 * This function intentionally consumes CPU cycles.
 */
void run_busy_loop(int duration_seconds)
{
    struct timespec start_time;
    struct timespec current_time;

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    while (1) {
        /* Trivial computation to prevent compiler optimization */
        volatile unsigned long counter = 0;
        counter++;

        clock_gettime(CLOCK_MONOTONIC, &current_time);

        long elapsed_seconds =
            current_time.tv_sec - start_time.tv_sec;

        if (elapsed_seconds >= duration_seconds) {
            break;
        }
    }
}

/*
 * Sleep for the specified duration.
 * Sleeping in chunks ensures robustness.
 */
void run_sleep_phase(int duration_seconds)
{
    int remaining = duration_seconds;

    while (remaining > 0) {
        remaining = sleep(remaining);
    }
}

int main(void)
{
    while (1) {
        printf("Entering busy phase (CPU active for 10 minutes)...\n");
        fflush(stdout);

        run_busy_loop(BUSY_DURATION_SECONDS);

        printf("Busy phase complete. Entering sleep phase (idle for 10 hours)...\n");
        fflush(stdout);

        run_sleep_phase(SLEEP_DURATION_SECONDS);
    }

    return 0;
}
