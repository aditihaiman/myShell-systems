#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>








int main() {
    int x = 1;
    
    while(x) {
        char * s;
        printf("$ ");
        fgets(s, 100, stdin);
        if (strcmp(s,"exit\n")==0) x = 0;

        //printf("s:%s cmp: %d\n", s, strcmp(s, "exit\n"));
        
        //sleep(0.5);
    }
    
    
    return 0;
}
