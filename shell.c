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
        
        if (strcmp(s,"exit")==0) x = 0;
        //printf("%s\n", s);
        
        //sleep(0.5);
    }
    
    
    return 0;
}
