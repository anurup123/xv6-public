// test_count.c
#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    int count = count_running_processes();  // Call the system call
    printf(1, "Total active processes: %d\n", count);  // Print the result
    exit();
}
