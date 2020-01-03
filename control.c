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

int remove_semaphore(){
  int semd;
  int shmd;
  semd = semget(KEY, 1, 0);
  shmd = shmget(KEY, 1, 0);

  printf("trying to get in\n");
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_op = -1;
  semop(semd, &sb, 1);
  //code to view, then remove
  view();
  shmctl(shmd, IPC_RMID, 0);
  printf("shared memory removed\n");
  remove_semaphore(filename);
  printf("file removed\n");
  semctl(semd, IPC_RMID, 0);
  printf("semaphore removed\n");

  sb.sem_op = 1;
  semop(semd, &sb, 1);
}


int control(char * option){ //command string
  if (!strcmp(option, "-c")) create_semaphore();
  else if (!strcmp(option, "-v")) view();
  else if (!strcmp(option, "-r")) remove_semaphore();
}

int view(){
  printf("The story so far: \n");
  f = fopen(filename, "r");
  char line[SEG_SIZE];
  while(fgets(line, SEG_SIZE, f)){
    printf("%s", line);
  }
  fclose(f);
}

char ** parse_args(char *line, char * sep){
  char ** ans = calloc(1024, sizeof(char));
  char *curr = line;
  int count = 0;
  while (curr){
    if (!strcmp(sep, " ")){
      char *temp = strsep(&curr, sep);
      if(strcmp(temp , "")){
        ans[count]= temp;
        count++;
      }
    }
    else{
      ans[count] = strsep(&curr, sep);
      count++;
    }
  }
  return ans;
}

int main(int argc, char *argv[]) {
    char* input = argv[1];
    //printf("Option chosen: %s\n", input);
    control(input);
    return 0;
  }
