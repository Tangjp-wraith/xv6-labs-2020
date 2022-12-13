#include "kernel/types.h"
#include "user/user.h"

#define MSGSIZE 16

int main(int argc, int *argv[]) {
  int pd[2];
  pipe(pd);
  char buf[MSGSIZE];
  int pid = fork();
  if (pid > 0) {
    write(pd[1], "ping", MSGSIZE);
    wait((int *)0);
    read(pd[0], buf, MSGSIZE);
    printf("%d: received %s\n", getpid(), buf);
  } else {
    read(pd[0], buf, MSGSIZE);
    printf("%d: received %s\n", getpid(), buf);
    write(pd[1], "pong", MSGSIZE);
  }
  close(pd[0]);
  close(pd[1]);
  exit(0);
}