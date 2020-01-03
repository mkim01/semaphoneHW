#include "control.h"

int control(char * option){ //command string
  if (!strcmp(option, "-c")) create_semaphore();
  else if (!strcmp(option, "-v")) view();
  else if (!strcmp(option, "-r")) remove_semaphore();
}

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

int remove_semaphore(){
  printf("Removing Mode Enabled:\n");

  int semd = semget(KEY, 1, 0);
  int shmd = shmget(KEY, 1, 0);
  shmctl(shmd, IPC_RMID, 0);
  printf("Removed shared memory segment.\n");
  semctl(semd, IPC_RMID, 0);
  printf("Removed semaphore.\n");
  view();
  remove(filename);
  printf("File removed.\n");
}

int view(){
  printf("The story so far: \n");
  f = fopen(filename, "r");
  char line[SEG_SIZE];
  while(fgets(line, SEG_SIZE, f)){
    printf("%s", line);
  }
}

int main(int argc, char *argv[]) {
    char* input = argv[1];
    //printf("Option chosen: %s\n", input);
    control(input);
    return 0;
  }
