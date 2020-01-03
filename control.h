#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <errno.h>

#define KEY 24602
#define SEG_SIZE 200
FILE *f;
char *filename = "file.txt";

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short  *array;
  struct seminfo  *__buf;
};
int create_semaphore();
int remove_semaphore();
int control(char * option);
int view();
char ** parse_args(char *line, char * sep);
