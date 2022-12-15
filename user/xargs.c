#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"
#include "kernel/stat.h"

#define SIZE 16

int main(int argc, char *argv[]) {
  char buf[SIZE];
  read(0, buf, SIZE);
  char *xargv[MAXARG];
  int xagrc = 0;
  for (int i = 1; i < argc; i++) {
    xargv[xagrc++] = argv[i];
  }
  char *p = buf;
  for (int i = 0; i < SIZE; i++) {
    if (buf[i] == '\n') {
      int pid = fork();
      if (pid > 0) {
        p = &buf[i + 1];
        wait((int *)0);
      } else {
        buf[i] = 0;
        xargv[xagrc++] = p;
        exec(xargv[0], xargv);
        exit(0);
      }
    }
  }
  wait((int *)0);
  exit(0);
}