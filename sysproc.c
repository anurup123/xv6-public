#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
int
sys_getyear(void)
{
    return 1975;
}

int sys_count_running_processes(void) {
    return count_running_processes();  // Call the helper function in proc.c
}
// In sysproc.c
// int sys_nice(void) {
//     int pid, value;

//     // Retrieve arguments passed from the user space
//     if (argint(0, &pid) < 0 || argint(1, &value) < 0)
//         return -1;

//     return set_nice(pid, value);
// }


// version 2 
// int sys_nice(void) {
//     int pid, value;
//     int old_nice;

//     if (argint(0, &pid) < 0) {
//         // If first argument retrieval fails, assume only 'value' is provided
//         if (argint(0, &value) < 0)
//             return -1;
//         pid = myproc()->pid;
//     } else {
//         // If two arguments are provided, get the second one
//         if (argint(1, &value) < 0)
//             return -1;
//     }

//     if (set_nice(pid, value) == -1)
//         return -1;  // PID not found

//     return old_nice;  // Return the old nice value
// }



// int sys_nice(void) {
//     int pid, value;
//     int old_nice;

//     // Attempt to retrieve the first argument as pid
//     if(argint(0, &pid) < 0) {
//         // If the first argument retrieval fails, assume only 'value' is provided
//         if(argint(0, &value) < 0)
//             return -1;  // Insufficient arguments

//         pid = myproc()->pid;  // Use current process's PID
//     } else {
//         // If two arguments are provided, get the second one as 'value'
//         if(argint(1, &value) < 0)
//             return -1;  // Insufficient arguments
//     }

//     // Call set_nice to update the nice value
//     if(set_nice(pid, value, &old_nice) == -1)
//         return -1;  // PID not found

//     return old_nice;  // Return the old nice value
// }


//versin old

int sys_nice(void) {
    int pid, value;

    // Retrieve arguments passed from the user space
    if (argint(0, &pid) < 0 || argint(1, &value) < 0)
        return -1;

    return set_nice(pid, value);
}
