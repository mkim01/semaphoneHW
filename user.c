#include "control.h"

int main() {
  int semd = semget(KEY, 1, 0);
        int shmd = shmget(KEY, 1, 0);
        struct sembuf stempd;
        stempd.sem_flg = SEM_UNDO;
        stempd.sem_op = -1;
        stempd.sem_num = 0;

        //Checking to see if semd and shmd exist.
        if(semd == -1) {
                printf("The sempahore does not exist. Please run ./control -c to create it.\n");
        }

        if(shmd == -1) {
                printf("The shared memory does not exist. Please run ./control -c to create it.\n");
                stempd.sem_op = 1;
                semop(semd, &stempd, 1);
        }

        //Prompt user for input.
        char *memory;
        memory = shmat(shmd,0,0);
        printf("Last addition: %s\n", memory);
        printf("Your addition: ");
        char input[SEG_SIZE];
        fgets(memory, SEG_SIZE, stdin);
        strcpy(input, memory);

        //File handling
        int fd = open(filename, O_RDWR | O_APPEND, 644);

        //Write user input.
        write(fd,input,strlen(input));
        close(fd);

        //Remove memory and stop shared memory process.
        stempd.sem_op = 1;
        semop(semd, &stempd, 1);
        shmdt(memory);
}
