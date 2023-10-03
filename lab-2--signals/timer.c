/* timer.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
int invokestate = 0;
int count = 0;
int count2 = 0;
void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  invokestate = 1;
count++; //count seconds
 // exit(1); //exit after printing
}
void term_handler(int signum){
  printf("\nProgram ran %d alarms for %d seconds.\n",count2,count);
  exit(1);
}

int main(int argc, char * argv[])
{
  signal(SIGALRM,handler); //register handler to handle SIGALRM
  signal(SIGINT,term_handler);
  while(invokestate!= -1){
  alarm(1); //Schedule a SIGALRM for 1 second
  count2++; //count aalarms
  while(!invokestate);
printf("Turing was right!\n");
invokestate = 0; //reset state
}
  return 0; //never reached
}