#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
void ParentProcess(int []);
void ChildProcess(int []);
void  ClientProcess(int []);

int  main(int  argc, char *argv[])
{
     int    ShmID;
     int    *ShmPTR;
     pid_t  pid;
     int    status;

     if (argc != 5) {
          printf("Use: %s #1 #2 #3 #4\n", argv[0]);
          exit(1);
     }

     ShmID = shmget(IPC_PRIVATE, 2*sizeof(int), IPC_CREAT | 0666);
     if (ShmID < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }
     printf("Server has received a shared memory of four integers...\n");

     ShmPTR = (int *) shmat(ShmID, NULL, 0);
     if (*ShmPTR == -1) {
          printf("*** shmat error (server) ***\n");
          exit(1);
     }
     printf("Server has attached the shared memory...\n");

     ShmPTR[0] = atoi(argv[1]);
     ShmPTR[1] = atoi(argv[2]);
    // ShmPTR[2] = atoi(argv[3]);
    // ShmPTR[3] = atoi(argv[4]);
     printf("Server has filled %d %d in shared memory...\n",
            ShmPTR[0], ShmPTR[1]);

     printf("Server is about to fork a child process...\n");
     pid = fork();
     if (pid < 0) {
          printf("*** fork error (server) ***\n");
          exit(1);
     }
     else if (pid == 0) {
          ClientProcess(ShmPTR);
          exit(0);
     } 
     ParentProcess(ShmPTR);
     wait(&status);
     printf("Server has detected the completion of its child...\n");
     shmdt((void *) ShmPTR);
     printf("Server has detached its shared memory...\n");
     shmctl(ShmID, IPC_RMID, NULL);
     printf("Server has removed its shared memory...\n");
     printf("Server exits...\n");
     exit(0);
}
void ParentProcess(int SharedMem[]){
srand(time(NULL));
int i;
for(i = 0; i < 25; i++){
  sleep(rand()% 6);

  SharedMem[1]=0;
  int acc = SharedMem[0];
  while(SharedMem[1] !=1){}
  if(acc <=100){
    int bal = rand() % 101;
    if( bal % 2 == 0){
      SharedMem[0] += bal;
      printf("Dear old Dad: Deposits $%d / Balance = $%d\n", bal, acc);
    }
    else if( bal % 2 != 0){
      printf("Dear old Dad: Doesn't have any money to give\n");
    }
  }
  else{
    printf("Dear old Dad: Thinks Student has enough Cash ($%d)\n", acc);
  }
SharedMem[1]=1;
}



}

void ChildProcess(int SharedMem[]){
srand(time(NULL));
int i;
for(i = 0; i < 25; i++){
  sleep(rand()% 6);

  SharedMem[1]=1;
  int acc = SharedMem[0];
  while(SharedMem[1] !=0){}
  
    int bal = rand() % 51;
    printf("Poor Student needs $%d\n", bal);

    if( bal <= acc){
      SharedMem[0] -= bal;
            printf("Poor Student: Withdraws $%d / Balance = $%d\n", bal, SharedMem[0]);
    }
    else {
            printf("Poor Student: Not Enough Cash ($%d)\n", acc);
    }
  
  
SharedMem[1]=0;
}



}

void  ClientProcess(int  SharedMem[])
{
     printf("   Client process started\n");
     printf("   Client found %d %d %d %d in shared memory\n",
                SharedMem[0], SharedMem[1], SharedMem[2], SharedMem[3]);
     printf("   Client is about to exit\n");
}