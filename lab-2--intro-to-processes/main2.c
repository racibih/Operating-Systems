#include  <stdio.h>
#include  <sys/types.h>
 #include <stdlib.h>
 #include <time.h> //for srand
 #include<unistd.h> //for sleep function

#define   MAX_COUNT  400


long int random(void);
void srandom(unsigned int seed);
char *initstate(unsigned int seed, char *state, size_t n);
char *setstate(char *state);

void  ChildProcess(int,int);                /* child process prototype  */
void  ParentProcess(void);               /* parent process prototype */

void  main(void)
{
  srand (time(NULL)); //seed random
  ParentProcess();      
}

void  ChildProcess(int child, int parent)
{     //takes in pid child and ppid parent
     int   i;
     int rand = random() % 30; //random no. of times <=30
     for (i = 1; i <= rand; i++){
     printf("Child Pid: %d is going to sleep!\n",child);
     sleep(random() % 10); //random no. of seconds <=10
     printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n",child,parent);
     
     }
     exit(0);
          //printf("   This line is from child, value = %d\n", i);
    // printf("   *** Child process is done ***\n");
}

void  ParentProcess(void)
{
     pid_t child1;
     pid_t child2;
     int c1pid;
     int c2pid;
     int ppid;
     // child 1 process
     child1 = fork();
     
     if (child1 == 0) {
      c1pid = getpid();
      ppid = getppid();
          ChildProcess(c1pid,ppid);

     } // child 2 process
     else{
     child2 = fork();
     if (child2 == 0) {
      c2pid = getpid();
      ppid = getppid();
          ChildProcess(c2pid,ppid);

     }
     else{ // parent process
       int returnStatus; 
       //print in order of who finishes first
      pid_t cpid1 = wait(&returnStatus);
      printf("Child Pid: %d has completed\n", cpid1);
      pid_t cpid2 = wait(&returnStatus);
      printf("Child Pid: %d has completed\n", cpid2);    
    



     }
     }
  
     //int   i;

     //for (i = 1; i <= MAX_COUNT; i++)
     //     printf("This line is from parent, value = %d\n", i);
     //printf("*** Parent is done ***\n");
}