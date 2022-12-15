#include "kernel/types.h"
#include "user/user.h"

#define SIZE 36
#define TRUE '1'
#define FALSE '0'

void prime(int pipe_read, int pipe_write) {
  char buf[SIZE];
  int val = 0;
  read(pipe_read, buf, SIZE);
  for (int i = 2; i < SIZE; ++i) {
    if (buf[i] == TRUE) {
      val = i;
      break;
    }
  }
  if (val == 0) {
    exit(0);
  }
  printf("prime %d\n", val);
  for (int i = val; i < SIZE; ++i) {
    if (i % val == 0) {
      buf[i] = FALSE;
    }
  }
  int pid = fork();
  if (pid > 0) {
    write(pipe_write, buf, SIZE);
  } else {
    prime(pipe_read, pipe_write);
  }
}

int main(int agrc, int *agrv[]) {
  int pd[2];
  pipe(pd);
  char nums[SIZE];
  for (int i = 0; i < SIZE; ++i) {
    nums[i] = TRUE;
  }
  nums[0] = FALSE;
  nums[1] = FALSE;
  int pid = fork();
  if (pid > 0) {
    write(pd[1], nums, SIZE);
    wait((int *)0);
  } else {
    prime(pd[0], pd[1]);
  }
  wait((int *)0);
  close(pd[0]);
  close(pd[1]);
  exit(0);
}