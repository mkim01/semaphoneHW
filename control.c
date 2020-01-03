#include "control.h"

int create_semaphore(){

  //semaphore
  int semd;
  int v, r;
  char input[3];
  semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  if (semd == -1) {
    printf("error %d: %s\n", errno, strerror(errno));
    semd = semget(KEY, 1, 0);
    v = semctl(semd, 0, GETVAL, 0);
    printf("semaphore created\n");
  }
  else {
    union semun us;
    us.val = 1;
    r = semctl(semd, 0, SETVAL, us);
    printf("semaphore created\n");
  }

  //shared memory
  int shm;
  char * data;
  shm = shmget(KEY, SEG_SIZE, IPC_CREAT | 0644);
  data = shmat(shm, 0, 0);
  printf("shared memory allocated\n");

  //file
  f = fopen(filename, "w");
  printf("file created\n");
}
