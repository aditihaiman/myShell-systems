#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>


char ** parse_args( char * line ) {
    char ** args = malloc(5 * sizeof(char *));
    char *s1 = line;
    int idx = 0;
    char *s;
    while(line != NULL){
        args[idx] = strsep( &line, " ");
        idx++;
    }
    args[idx] = NULL;
    return args;
}

int main() {
    int x = 1;
    
    while(x) {
        char s[100];
        printf("$ ");
        fgets(s, 100, stdin);
        char * new = s;
        char * command = strsep(&new, "\n"); //Removes \n from user input
        char ** args = parse_args(command); //creates list with command to execute

        if (strcmp(args[0],"exit")==0) { //exit
            printf("[Process completed]\n");
            break;
        }
        else if (strcmp(args[0], "cd")==0){ //change directory
            //printf("path: %s\n", args[1]);
            chdir(args[1]);
            //printf("errno: %d  error: %s\n", errno, strerror(errno));
        }
        
        else {
            int child = fork();

            if (child == 0) { //creates child process to execute command
                execvp(args[0], args);
            }

            else {
                wait(NULL);

            }
        }
        //printf("s:%s cmp: %d\n", s, strcmp(s, "exit\n"));
        
        //sleep(0.5);
    }
    
    
    return 0;
}
