#include "types.h"
#include "stat.h"
#include "user.h"

#define PGSIZE 4096
#define MAXPAGES 1024

int main(int argc, char *argv[]) {
    int jump = PGSIZE / sizeof(int);

    printf(1, "PageCount\tTrials\tTicks\tPageFaults\n");

    for (int numpages = 1; numpages <= MAXPAGES; numpages *= 2) {
        int trials = 5000000;
        int faults_before = getpagefaults();

        uint start = uptime();
        int *arr = (int*) sbrk(numpages * PGSIZE);

        if (arr == (void*)-1) {
            printf(1, "sbrk failed for %d pages\n", numpages);
            exit();
        }

        for (int t = 0; t < trials; t++) {
            for (int i = 0; i < (numpages/2) * jump; i += jump) {
                arr[i] += 1;   // touch pages
            }
        }

        uint end = uptime();
        int faults_after = getpagefaults();

        printf(1, "%d\t\t%d\t%d\t%d\n", numpages, trials, end - start, faults_after - faults_before);
    }

    exit();
}
