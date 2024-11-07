// // In user/nice.c
// #include "types.h"
// #include "stat.h"
// #include "user.h"

// int main(int argc, char *argv[]) {
//     int pid, value, old_value;

//     if (argc < 2) {
//         printf(2, "Usage: nice <pid> <value> or nice <value>\n");
//         exit();
//     }

//     if (argc == 2) {
//         pid = getpid();  // Assume current process if only value is given
//         value = atoi(argv[1]);
//     } else {
//         pid = atoi(argv[1]);
//         value = atoi(argv[2]);
//     }

//     old_value = nice(pid, value);  // Call the system call
//     if (old_value < 0) {
//         printf(2, "Error: Failed to set nice value.\n");
//     } else {
//         printf(1, "%d %d\n", pid, old_value);
//     }

//     exit();
// }



// // In user/nice.c
// #include "types.h"
// #include "stat.h"
// #include "user.h"
// #include "fcntl.h"

// // Function to check if a string is a valid integer
// int is_number(char *str) {
//     if(str == 0)
//         return 0;
//     for(int i = 0; str[i] != '\0'; i++) {
//         if(str[i] < '0' || str[i] > '9')
//             return 0;
//     }
//     return 1;
// }

// int main(int argc, char *argv[]) {
//     int pid, value, old_nice;

//     if(argc < 2 || argc > 3) {
//         printf(2, "Usage: nice <pid> <value> or nice <value>\n");
//         exit();
//     }

//     if(argc == 2) {
//         // Only value provided; apply to current process
//         if(!is_number(argv[1])) {
//             printf(2, "Error: Value must be an integer.\n");
//             exit();
//         }
//         pid = getpid();  // Retrieve current process's PID
//         value = atoi(argv[1]);
//     } else {
//         // PID and value provided
//         if(!is_number(argv[1]) || !is_number(argv[2])) {
//             printf(2, "Error: PID and Value must be integers.\n");
//             exit();
//         }
//         pid = atoi(argv[1]);
//         value = atoi(argv[2]);
//     }

//     old_nice = nice(pid, value);  // Call the system call

//     if(old_nice == -1) {
//         printf(2, "Error: Failed to set nice value for PID %d.\n", pid);
//     } else {
//         printf(1, "%d %d\n", pid, old_nice);  // Output PID and old nice value
//     }

//     exit();
// }

//good one 
// #include "types.h"
// #include "stat.h"
// #include "user.h"

// int main(int argc, char *argv[]) {
//     int pid, value, old_value;

//     if (argc < 2) {
//         printf(2, "Usage: nice <pid> <value> or nice <value>\n");
//         exit();
//     }

//     if (argc == 2) {
//         pid = getpid();  // Assume current process if only value is given
//         value = atoi(argv[1]);
//     } else {
//         pid = atoi(argv[1]);
//         value = atoi(argv[2]);
//     }

//     old_value = nice(pid, value);  // Call the system call
//     if (old_value < 0) {
//         printf(2, "Error: Failed to set nice value.\n");
//     } else {
//         printf(1, "%d %d\n", pid, old_value);
//     }

//     exit();
// }




#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    int pid, value, old_value;

    if (argc < 2) {
        printf(2, "Usage: nice <pid> <value> or nice <value>\n");
        exit();
    }

    if (argc == 2) {
        pid = getpid();  // Assume current process if only value is given
        value = atoi(argv[1]);
    } else {
        pid = atoi(argv[1]);
        value = atoi(argv[2]);
    }

    old_value = nice(pid, value);  // Call the system call
    if (old_value < 0) {
        printf(2, "Error: Failed to set nice value.\n");
    } else {
        printf(1, "%d %d\n", pid, old_value);
    }

    exit();
}
