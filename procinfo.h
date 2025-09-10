#ifndef _PROCINFO_H_
#define _PROCINFO_H_

#include "types.h"

struct proc_info {
  int pid;
  char name[16];
  char state[16];
  int sz;
};

#endif // _PROCINFO_H_