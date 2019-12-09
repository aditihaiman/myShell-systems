#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>


char ** parse_args( char * line ) {
    char ** args = malloc(10 * sizeof(char *));
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

char ** parse_mult_args( char * line ) {
    char ** args = malloc(10 * sizeof(char *));
    char *s1 = line;
    int idx = 0;
    char *s;
    while(line != NULL){
        args[idx] = strsep( &line, ";");
        idx++;
    }
    args[idx] = NULL;
    return args;
}

int redirect_stdin(char * filename){
    int fd = open(filename, O_CREAT, 0644);
    //int backup = dup(STDIN_FILENO);
    dup2(fd, STDIN_FILENO);
    return fd;
}

int redirect_stdout(char * filename){
    int fd = open(filename, O_CREAT, 0644);
    //int backup = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    return fd;
}

int main() {
    int x = 1;
    
    while(x) {
        char s[100];
        printf("$ ");
        fgets(s, 100, stdin);
        char * new = s;
        char * command = strsep(&new, "\n"); //Removes \n from user input
        char ** mult_args = parse_mult_args(command);
        int idx = 0;
        while (mult_args[idx] != NULL) { //loops through each separate command
            //char * line = mult_args[idx];
            
            //printf("line: %s\n", line);
            
            char ** args = parse_args(mult_args[idx]); //creates list with command to execute
            
            //char ** copy = args;
            
//            if (strstr(line, ">")!=NULL){
//                printf("B\n");
//                int idx2 = 0;
//                while (args[idx2] != NULL) {
//                    printf("A\n");
//                    printf("arg %d: %s\n", idx2, args[idx2]);
//                    if (strcmp(args[idx2], ">")==0) redirect_stdout(args[idx2+1]);
//                    idx2++;
//                }
//            }
//            if (strstr(line, "<")!=NULL){
//                int idx2 = 0;
//                while (args[idx2] != NULL) {
//                    if (strcmp(args[idx2], ">")==0) redirect_stdin(args[idx2+1]);
//                    idx2++;
//                }
//            }
//
            if (strcmp(args[0],"exit")==0) { //exit
                printf("[Process completed]\n");
                goto end;
            }
            else if (strcmp(args[0], "cd")==0){ //change directory
                chdir(args[1]);
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
            
            //undo redirection
            
            idx++;
        }
    }
    
    end:
    return 0;
}
