#include "kernel/types.h"
#include "user/user.h" 

int main() {
    int pid;
    int pip[2];
    pipe(pip); 
    char txt[20];
    if((pid = fork()) == 0) { 
        read(pip[0], txt, 10); 
        printf("%d: received %s\n", getpid(), txt);
        write(pip[1], "pong", 10); 
        exit(0);
    }
    else { 
        write(pip[1], "ping", 10); 
        wait(0); 
        read(pip[0], txt, 10); 
        printf("%d: received %s\n", getpid(), txt);
        exit(0);
    }
    exit(0);
}