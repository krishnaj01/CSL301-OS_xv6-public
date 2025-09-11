#include "types.h"
#include "stat.h"
#include "user.h"

#define PGSIZE 4096
#define MAXPAGES 1024

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf(1, "Usage: tlbtest <numpages> <trials>\n");
        exit();
    }

    int numpages = atoi(argv[1]);
    int trials = atoi(argv[2]);

    if (numpages < 1 || numpages > MAXPAGES) {
        printf(1, "numpages out of range (1..%d)\n", MAXPAGES);
        exit();
    }

    int jump = PGSIZE / sizeof(int);

    // Dynamically allocate pages using sbrk()
    int *arr = (int*) sbrk(numpages * PGSIZE);
    if (arr == (void*)-1) {
        printf(1, "sbrk failed for %d pages\n", numpages);
        exit();
    }

    // Get page fault count before test
    int pf_before = getpagefaults();
    
    // Start timing
    uint start = uptime();

    // Access pages to trigger lazy allocation page faults
    for (int t = 0; t < trials; t++) {
        for (int i = 0; i < (numpages/2) * jump; i += jump) {
            arr[i] += 1;   // trigger page faults on first access
        }
    }

    // End timing
    uint end = uptime();

    // Page fault count after test
    int pf_after = getpagefaults();

    printf(1, "Pages: %d\tTrials: %d\tTicks: %d\tPageFaults: %d\n", numpages, trials, end - start, pf_after - pf_before);

    exit();
}