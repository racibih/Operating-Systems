/*Rachel Ibihwiori*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
 #include <time.h> //for srand
#include <signal.h>
//include this for path length
#include <linux/limits.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128
#define   MAX_COUNT  400

long int random(void);
void srandom(unsigned int seed);
char *initstate(unsigned int seed, char *state, size_t n);
char *setstate(char *state);
pid_t child;

char prompt[PATH_MAX+3] = "> ";
char delimiters[] = " \t\r\n";
extern char **environ;
char *getcwd(char *buf, size_t size);
//function to tokenize strings
char * strtok(char str[], const char delims[]);
//get env
//char getenv(const char *name);
int setenv(const char *name, const char *value, int overwrite);
void tokenize(char *command_line, char *arguments[], char *prompt) {
    int i;
    char *token;
  
    // Read in the first token
    token = strtok(command_line, delimiters);
    arguments[0] = token;

    // For the rest of the input, read each word separated by the delimiters into the arguments array
    for (i = 1; i < MAX_COMMAND_LINE_ARGS; i++) {
        token = strtok(NULL, delimiters);
        arguments[i] = token;
        if (token != NULL && token[0] == '$') {
            const char *newtoken = token + 1;
            char *nvar = getenv(newtoken);
            arguments[i] = nvar;
        }
    }
    }
    
// Function to implement the cd command
void excd(char *arguments[]) {
    if (arguments[1] == NULL) {
        // If no directory is provided, change to the user's home directory
        if (chdir(getenv("HOME")) != 0) {
            perror("chdir");
        }
    } else {
        if (chdir(arguments[1]) != 0) {
            perror("chdir");
        }
    }
}
void exexit() {
    exit(0);
}
// Function to implement the pwd command
void expwd() {
    char path[PATH_MAX];
    if (getcwd(path, sizeof(path)) != NULL) {
        printf("%s\n", path);
    } else {
        perror("getcwd");
    }
}
    // Function to implement the echo command
    
void execho(char *arguments[]) {
    int i = 1;
    while (arguments[i]) {
        printf("%s ", arguments[i]);
        i++;
    }
    printf("\n");
}
//because c doesn't have overloading env is implemented by taking arguments and checking if it has a variable following 'env', then it does the command like echo
// Function to implement the env command
void exenv(char *arguments[]) {
  if(arguments[1]==NULL){
    char **env = environ;
    while (*env != NULL) {
        printf("%s\n", *env);
        env++;
    }
  }
  else{
     int i = 1;
     
    while (arguments[i]) {
      char *nvar = getenv(arguments[i]);
      arguments[i]=nvar;
        printf("%s ", arguments[i]);
        i++;
    }
    printf("\n");
  }
}
// Function to implement the setenv command
void exsetenv(char *arguments[]) {

  char* value;
  char* variable;
  variable= strtok(arguments[1],"=");
  value = strtok(NULL, "=");

    if (arguments[1] != NULL) {
        int overwrite = 1;
        if (setenv(variable, value, overwrite) != 0) {
            perror("setenv");
        }
    } else {
        perror("setenv");
    }
}
void alarmhandler( int sig){
  kill(child, sig);
}
void  ChildProcess(char *arguments[])
{     
      execvp(arguments[0],arguments);
      perror("execvp() failed");
      exit(1);
     
     
     }
    

void  ParentProcess(char *arguments[], int is_background)
{
    child = fork();
    int status;
    pid_t xpid;

     // child 1 process
     if(child < 0){
     perror("Fork failed");
     }

     else if (child == 0) {
     execvp(arguments[0],arguments);
      perror("execvp() failed");
      exit(1);

     } 
     
     else{
      if(is_background==1){
      //  printf("running in the background: %s\n",arguments[0]);
                  printf("%s\n", prompt);

      }else{
        signal(SIGALRM, alarmhandler);
        alarm(10);
      waitpid(child, &status, 0);


      if(WIFEXITED(status) && WEXITSTATUS(status)==1){
      printf("An error occurred.\n");
      }
      }
    
}
}
void signalhandler(int sig) {
   
              printf("\n%s", prompt);
                          fflush(stdout);

 // Print a prompt after receiving SIGINT
    
}



int main() {
    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];
    char cmd_bak[MAX_COMMAND_LINE_LEN];
  //create token
  char* token;
    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];
    signal(SIGINT,signalhandler); 
    while (true) {
      
        do{     	

            // Print the shell prompt.
            printf("%s", prompt);
            fflush(stdout);
           
            // Read input from stdin and store it in command_line. If there's an
            // error, exit immediately. (If you want to learn more about this line,
            // you can Google "man fgets")
        
            if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
                fprintf(stderr, "fgets error");
                exit(0);
            }
 
        }while(command_line[0] == 0x0A);  // while just ENTER pressed

      
        // If the user input was EOF (ctrl+d), exit the shell.
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }
        int is_background = 0;
       char *backgroundpos = strchr(command_line, '&');
        if(backgroundpos != NULL){
          is_background = 1;
         *backgroundpos = '\0';
        }
        else{
          is_background =0;
        }
        // TODO:
        // 
        
			  // 0. Modify the prompt to print the current working directory
           //getcwd modifies prompt to contain cwd
           //if theres a null value print error message
            if(getcwd(prompt, PATH_MAX)==NULL){
              perror("getcwd() error");
            }
            //no error, continue 
            else{
                //adding >
                   strcat(prompt, "> ");
                   fflush(stdout);

            }
            
			
        // 1. Tokenize the command line input (split it on whitespace)
      /*
      void tokenize(){
            
        int i;
        //read in first token
        token = strtok(command_line,delimiters);
        arguments[0]=token;
        
        //for the rest of the input read each word separated by the delimiters into arguments array
        for(i=1; i < MAX_COMMAND_LINE_ARGS; i++){
            token = strtok(NULL,delimiters);
            arguments[i]=token;
            if(token[0]=='$'){
                const char* newtoken = token+1;
                 char* nvar; 
                nvar = getenv(newtoken);
                arguments[i]= nvar;
                printf("%s",arguments[i]);
                continue;
                }
            
            

            //printf("%s",arguments[i]);
           
        }
         switch(arguments[0]){
                case "echo" :
                case "cd":
                case "pwd":
                case "exit":
                case "env":
                case "setenv":


            } 
        }*/        
        tokenize(command_line, arguments, prompt);
 if (strcmp(arguments[0], "echo") == 0) {
        execho(arguments);
    } else if (strcmp(arguments[0], "env") == 0) {
        exenv(arguments);
    } else if (strcmp(arguments[0], "setenv") == 0) {
        exsetenv(arguments);
    } 
      else if (strcmp(arguments[0], "cd") == 0) {
        excd(arguments);
    } else if (strcmp(arguments[0], "pwd") == 0) {
        expwd();
    } else if (strcmp(arguments[0], "exit") == 0) {
        exexit();
    } else {
        // For other commands, you can implement the logic here
       // printf("Command not recognized: %s\n", arguments[0]);
    
    ParentProcess(arguments,is_background);
    
    }


    


        // 2. Implement Built-In Commands
       
      //cd 
      //pwd
      //echo
      //exit
      //env
      //setenv
    
        // 3. Create a child process which will execute the command line input

  
        // 4. The parent process should wait for the child to complete unless its a background process
      
      
        // Hints (put these into Google):
        // man fork
        // man execvp
        // man wait
        // man strtok
        // man environ
        // man signals
        
        // Extra Credit
        // man dup2
        // man open
        // man pipes
    }
    // This should never be reached.
    return -1;
}

