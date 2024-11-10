#include "types.h"
#include "stat.h"
#include "user.h"

#define TIME_LIMIT 100  // Time limit in ticks (about 1 second)

// Function to check if a number is prime
int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// Function to count primes within a given time limit
void count_primes(int priority_level) {
    int start_ticks = uptime();
    int prime_count = 0;

    // Count primes until TIME_LIMIT is reached
    for (int i = 2; uptime() - start_ticks < TIME_LIMIT; i++) {
        if (is_prime(i)) {
            prime_count++;
        }
    }
    printf(1,"%d-%d",priority_level,prime_count);
    //printf(1, "Priority Level %d - Prime Count: %d\n", priority_level, prime_count);
}

int main(void) {
    // Process 1: lowest priority
    int pid1 = fork();
    if (pid1 == 0) {
        #ifdef SCHEDPOLICY_PRIORITY
            set_nice(getpid(), 5);  // Set lowest priority
        #endif
        count_primes(5);
        exit();
    }

    // Process 2: medium priority
    int pid2 = fork();
    if (pid2 == 0) {
        #ifdef SCHEDPOLICY_PRIORITY
            set_nice(getpid(), 3);  // Set medium priority
        #endif
        count_primes(3);
        exit();
    }

    // Process 3: highest priority
    int pid3 = fork();
    if (pid3 == 0) {
        #ifdef SCHEDPOLICY_PRIORITY
            set_nice(getpid(), 1);  // Set highest priority
        #endif
        count_primes(1);
        exit();
    }

    // Wait for all child processes to complete
    wait();
    wait();
    wait();

    printf(1, "All processes have completed.\n");
    exit();
}
