#include "procinfo.h"
#include "user.h"

int main(int argc, char *argv[])
{
  if(argc != 2){
    printf(1, "Usage: pinfo <pid>\n");
    exit();
  }

  int pid = atoi(argv[1]);
  struct proc_info kinfo;

  int ret = getpinfo(pid, &kinfo);

  if(ret < 0){
    printf(1, "getpinfo: PID %d not found or error\n", pid);
    exit();
  }

  printf(1, "PID: %d\n", kinfo.pid);
  printf(1, "Name: %s\n", kinfo.name);
  printf(1, "State: %s\n", kinfo.state);
  printf(1, "Size: %d\n", kinfo.sz);

  exit();
}
