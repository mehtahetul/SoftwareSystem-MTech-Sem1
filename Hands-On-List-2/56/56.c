
/*
============================================================================
Name        : 56.c
Author      : Hetul Mehta
Description : Measure the time taken to execute 100 getppid() system calls
              using a timestamp counter on AArch64.
============================================================================
*/

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>

static inline uint64_t read_counter(void)
{
    uint64_t value;
    asm volatile("isb; mrs %0, cntvct_el0" : "=r"(value));
    return value;
}

static inline uint64_t read_counter_frequency(void)
{
    uint64_t value;
    asm volatile("mrs %0, cntfrq_el0" : "=r"(value));
    return value;
}

int main(void)
{
    uint64_t start, end, ticks, frequency;
    double time_ns;

    frequency = read_counter_frequency();

    start = read_counter();

    for (int i = 0; i < 100; i++)
    {
        getppid();
    }

    end = read_counter();

    ticks = end - start;
    time_ns = (double)ticks * 1e9 / frequency;

    printf("Counter frequency: %.2f MHz\n",
           frequency / 1e6);
    printf("100 getppid() calls took %llu counter ticks\n",
           (unsigned long long)ticks);
    printf("Approximate time: %.2f ns\n", time_ns);

    return 0;
}

/*
============================================================================
Sample Output (values vary by machine):
Counter frequency: 24.00 MHz
100 getppid() calls took 27282 counter ticks
Approximate time: 1136750.00 ns
============================================================================
*/

