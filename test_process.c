// #include "types.h"
// #include "stat.h"
// #include "user.h"

// // Function to check if a number is prime
// int is_prime(int num) {
//     int j;
//     if (num < 2) return 0;
//     for (j = 2; j * j <= num; j++) {
//         if (num % j == 0) return 0;
//     }
//     return 1;
// }

// // Function for each child process to print primes for a fixed duration
// void print_primes(int duration) {
//     int count = 0;
//     int i = 2;
//     int end_time = uptime() + duration;  // Run for `duration` ticks

//     while (uptime() < end_time) {
//         if (is_prime(i)) {
//             count++;
//         }
//         i++;
//     }
//     printf(1, "Process %d found %d primes.\n", getpid(), count);
// }

// int main() {
//     int num_children = 3;
//     int nice_values[] = {1, 3, 5};  // Nice values within the allowed range [1, 5]
//     int duration = 100;  // Duration in clock ticks for each child to run
//     int i;

//     for (i = 0; i < num_children; i++) {
//         int pid = fork();
//         if (pid == 0) {
//             // Child process
//             int old_nice = nice(getpid(), nice_values[i]);  // Set the nice value using set_nice
//             printf(1, "Child %d with old nice value %d and new nice value %d started...\n", getpid(), old_nice, nice_values[i]);
//             print_primes(duration);
//             printf(1, "Child %d with nice value %d finished.\n", getpid(), nice_values[i]);
//             exit();
//         } else if (pid < 0) {
//             printf(2, "fork failed\n");
//             exit();
//         }
//     }

//     // Parent process waits for all children
//     for (i = 0; i < num_children; i++) {
//         wait();
//     }

//     printf(1, "All children have finished.\n");
//     exit();
// }

//version 2
// #include "types.h"
// #include "stat.h"
// #include "user.h"
// #include "fcntl.h"

// // Function to check if a number is prime
// int is_prime(int num) {
//     int j;
//     if (num < 2) return 0;
//     for (j = 2; j * j <= num; j++) {
//         if (num % j == 0) return 0;
//     }
//     return 1;
// }

// // Function for each child process to print primes for a fixed duration
// void print_primes(int duration) {
//     int count = 0;
//     int i = 2;
//     int end_time = uptime() + duration;

//     while (uptime() < end_time) {
//         if (is_prime(i)) {
//             count++;
//         }
//         i++;
//     }

//     printf(1, "Process %d found %d primes.\n", getpid(), count);
// }

// int main() {
//     int num_children = 3;
//     int nice_values[] = {1, 3, 5};  // Nice values within the allowed range
//     int duration = 100;  // Duration in ticks for each child to run
//     int i;

//     for (i = 0; i < num_children; i++) {
//         int pid = fork();
//         if (pid == 0) {
//             // Child process
//             int old_nice = set_nice(getpid(), nice_values[i]);

//             // Buffer the output message to print all at once
//             printf(1, "Updating PID %d nice value from %d to %d\n", getpid(), old_nice, nice_values[i]);
//             printf(1, "Child %d with old nice value %d and new nice value %d started...\n", getpid(), old_nice, nice_values[i]);

//             print_primes(duration);  // Print primes

//             printf(1, "Child %d with nice value %d finished.\n", getpid(), nice_values[i]);
//             exit();
//         } else if (pid < 0) {
//             printf(2, "fork failed\n");
//             exit();
//         }
//     }

//     // Parent process waits for all children
//     for (i = 0; i < num_children; i++) {
//         wait();
//     }

//     printf(1, "All children have finished.\n");
//     exit();
// }


//code 1
// #include "types.h"
// #include "stat.h"
// #include "user.h"

// // Function to check if a number is prime
// int is_prime(int num) {
//     int j;
//     if (num < 2) return 0;
//     for (j = 2; j * j <= num; j++) {
//         if (num % j == 0) return 0;
//     }
//     return 1;
// }

// // Function for each child process to print primes for a fixed duration
// void print_primes(int duration) {
//     int count = 0;
//     int i = 2;
//     int end_time = uptime() + duration;  // Run for `duration` ticks

//     while (uptime() < end_time) {
//         if (is_prime(i)) {
//             count++;
//         }
//         i++;
//     }
//     printf(1, "Process %d found %d primes.\n", getpid(), count);
// }

// int main() {
//     int num_children = 3;
//     int nice_values[] = {1, 3, 5};  // Nice values within the allowed range [1, 5]
//     int duration = 100;  // Duration in clock ticks for each child to run
//     int i;

//     for (i = 0; i < num_children; i++) {
//         int pid = fork();
//         if (pid == 0) {
//             // Child process
//             int old_nice = set_nice(getpid(), nice_values[i]);  // Set the nice value
//             printf(1, "Updating PID %d nice value from %d to %d\n", getpid(), old_nice, nice_values[i]);
//             printf(1, "Child %d with old nice value %d and new nice value %d started...\n", getpid(), old_nice, nice_values[i]);
//             print_primes(duration);
//             printf(1, "Child %d with nice value %d finished.\n", getpid(), nice_values[i]);
//             exit();
//         } else if (pid < 0) {
//             printf(2, "fork failed\n");
//             exit();
//         }

//         // Wait for each child process to finish before starting the next
//         wait();
//     }

//     printf(1, "All children have finished.\n");
//     exit();
// }

// code 2 

#include "types.h"
#include "stat.h"
#include "user.h"

// Function to check if a number is prime
int is_prime(int num) {
    int j;
    if (num < 2) return 0;
    for (j = 2; j * j <= num; j++) {
        if (num % j == 0) return 0;
    }
    return 1;
}

// Function for each child process to print primes for a fixed duration
void print_primes(int duration) {
    int count = 0;
    int i = 2;
    int end_time = uptime() + duration;  // Run for `duration` ticks

    while (uptime() < end_time) {
        if (is_prime(i)) {
            // printf(1, "%d, process %d\n", i, getpid());
            
            count++;
        }
        i++;
    }
    printf(1, "Process %d found %d primes.\n", getpid(), count);
}

int main() {
    int num_children = 3;
    int nice_values[] = {1, 3, 5};  // Nice values within the allowed range [1, 5]
    int duration = 500;  // Duration in clock ticks for each child to run
    int i;

    for (i = 0; i < num_children; i++) {
        int pid = fork();
        if (pid == 0) {
            // Child process
            int old_nice = nice(getpid(), nice_values[i]);  // Set the nice value
            printf(1, "Child %d with old nice value %d and new nice value %d started...\n", getpid(), old_nice, nice_values[i]);
            print_primes(duration);
            printf(1, "Child %d with nice value %d finished.\n", getpid(), nice_values[i]);
            exit();
        } else if (pid < 0) {
            printf(2, "fork failed\n");
            exit();
        }
    }

    // Parent process waits for all children
    for (i = 0; i < num_children; i++) {
        wait();
    }

    printf(1, "All children have finished.\n");
    exit();
}


// //code 3 
// #include "types.h"
// #include "stat.h"
// #include "user.h"

// #define PRIORITY  // Ensure this is defined if using priority-based scheduling

// // Function to check if a number is prime
// int is_prime(int n) {
//     if (n <= 1) return 0;
//     for (int i = 2; i * i <= n; i++) {
//         if (n % i == 0) return 0;
//     }
//     return 1;
// }

// // Function to print primes up to 1000
// void print_primes() {
//     for (int i = 2; i < 1000; i++) {
//         if (is_prime(i)) {
//             printf(1, "PID %d: %d\n", getpid(), i);
//         }
//     }
// }

// int main(void) {
//     int pid1 = fork();
//     if (pid1 == 0) {
//         // Child process 1: lowest priority
//         #ifdef PRIORITY
//             set_nice(getpid(), 5);  // Set to lowest priority (adjust based on your `set_nice` range)
//             printf(1, "\nLowest Priority PID: %d\n", getpid());
//         #endif
//         print_primes();
//         exit();
//     }

//     int pid2 = fork();
//     if (pid2 == 0) {
//         // Child process 2: medium priority
//         #ifdef PRIORITY
//             set_nice(getpid(), 3);  // Medium priority
//             printf(1, "\nMedium Priority PID: %d\n", getpid());
//         #endif
//         print_primes();
//         exit();
//     }

//     int pid3 = fork();
//     if (pid3 == 0) {
//         // Child process 3: highest priority
//         #ifdef PRIORITY
//             set_nice(getpid(), 1);  // Highest priority
//             printf(1, "\nHighest Priority PID: %d\n", getpid());
//         #endif
//         print_primes();
//         exit();
//     }

//     // Wait for all child processes to finish
//     wait();
//     wait();
//     wait();
    
//     printf(1, "All children have finished.\n");
//     exit();
// }
