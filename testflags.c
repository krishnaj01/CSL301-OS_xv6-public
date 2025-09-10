#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    int val;
    
    // first set and get
    printf(1, "Setting flag to 1234...\n");
    if (setflag(1234) < 0) {
        printf(1, "Error: setflag failed\n");
        exit();
    }
    val = getflag();
    printf(1, "First flag value retrieved: %d\n", val);

    // second set and get
    printf(1, "Setting flag to 1250...\n");
    if (setflag(1250) < 0) {
        printf(1, "Error: setflag failed\n");
        exit();
    }
    val = getflag();
    printf(1, "Second flag value retrieved: %d\n", val);

    exit();
}