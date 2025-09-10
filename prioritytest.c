#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    int pid[5];
    int priorities[5] = {10, 1, 30, 60, 40};  // different priorities

    printf(1, "Starting priority scheduling test with 5 processes...\n");
    
    for (int i=0;i<5;i++) {
        pid[i] = fork();
        if (pid[i] == 0) {
            setpriority(priorities[i]);
            printf(1, "Child %d (pid %d) with priority %d started.\n", i+1, getpid(), priorities[i]);

            for (int j=0;j<50000000;j++) {}  // busy loop

            printf(1, "Child %d (pid %d) finished.\n", i+1, getpid());
            exit();
        }
    }

    for (int i=0;i<5;i++) wait();

    printf(1, "Priority scheduling test with 5 processes complete.\n");
    exit();
}