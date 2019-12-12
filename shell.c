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
    int backup = dup(STDIN_FILENO);
    int fd = open(filename, O_CREAT, 0644);
    fd = open(filename, O_RDWR);
    dup2(fd, STDIN_FILENO);
    return backup;
}

int redirect_stdout(char * filename){
    int backup = dup(STDOUT_FILENO);
    int fd = open(filename, O_CREAT, 0644);
    fd = open(filename, O_RDWR);
    dup2(fd, STDOUT_FILENO);
    return backup;
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
            char line[100];
            strcpy(line, mult_args[idx]);
            int stdout = 0;
            int stdin = 0;

            char ** args = parse_args(mult_args[idx]); //creates list with command to execute
            int backup;
            
            if (strstr(line, ">")!=NULL){
                int idx2 = 0;
                while (args[idx2] != NULL) {
                    if (strcmp(args[idx2], ">")==0) {
                        backup = redirect_stdout(args[idx2+1]);
                        args[idx2] = NULL;
                        args[idx2+1] = NULL;
                        stdout = 1;
                    }
                    idx2++;
                }
            }
            if (strstr(line, "<")!=NULL){
                int idx2 = 0;
                while (args[idx2] != NULL) {
                    if (strcmp(args[idx2], "<")==0) {
                        backup = redirect_stdin(args[idx2+1]);
                        args[idx2] = NULL;
                        args[idx2+1] = NULL;
                        stdin = 1;
                    }
                    idx2++;
    
                }
            }

            char * first_args = args[0];
            if (strstr(line, "|") != NULL) {
                FILE *p = popen(args[0], "r"); //open read end of pipe
                if (p == NULL) {
                    printf("error\n");
                }
                
                else {
                    char pipedCommands[100];
                    FILE *p2 = popen(args[2], "w"); //open write end of pipe
                    while (fgets( pipedCommands, sizeof(pipedCommands), p) != NULL) {
                        fputs(pipedCommands, p2); //write info to input of next command
                        //printf("%s->%s", args[0], pipedCommands);
                    }
                    pclose(p2);
                }
                pclose(p);
                break; //prevents command from being executed later
            }
            
            
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
            if (stdout) dup2(backup, STDOUT_FILENO);
            if (stdin) dup2(backup, STDIN_FILENO);
            
            idx++;
        }
    }
    
    end:
    return 0;
}
