#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


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
        char * command = strsep(&new, "\n");
        
        if (strcmp(command,"exit")==0) {
            x = 0;
        }
        
        int child = fork();

        if (child == 0) {
             char ** args = parse_args(command);
             execvp(args[0], args);
        }

        else {
            wait(NULL);

        }
        //printf("s:%s cmp: %d\n", s, strcmp(s, "exit\n"));
        
        //sleep(0.5);
    }
    
    
    return 0;
}
