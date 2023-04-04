#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc < 3){
    fprintf(2, "Usage: trace <mask> ...\n");
    exit(1);
  }

  trace(atoi(argv[1]));
  if (fork()) {
    wait(0);
  } else {
    exec(argv[2], &argv[2]);
  }

  exit(0);
}
