#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
int main(int argc, char **argv){
if(argc != 2){
  printf("Error: Number of arguments\n");
  return 1;
}


int pipefd1[2];
    int pipefd2[2];
    int pid1, pid2;

 char *cat_args[] = {"cat", "scores", NULL};
  char *grep_args[] = {"grep", argv[1], NULL};
 char *sort_args[] = {"sort", NULL};

//first pipe 
 pipe(pipefd1);
 pid1 = fork();
//child - grep
if(pid1 ==0){
  dup2(pipefd1[0], 0);
  close(pipefd1[1]);
  execvp("grep", grep_args);

}
//second pipe
pipe(pipefd2);
pid2 = fork();

if(pid2 ==0){

//replace input with second pipe input
dup2(pipefd2[0],0);
close(pipefd2[1]);
execvp("sort", sort_args);
}
dup2(pipefd1[1],1);
close(pipefd1[0]);
execvp("cat", cat_args);
wait(NULL);
wait(NULL);

return 0;

}