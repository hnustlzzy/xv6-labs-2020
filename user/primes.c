#include "kernel/types.h"
#include "user/user.h" 

void child(int* pipe1) {
    int cur, pid;
    close(pipe1[1]);
    if(read(pipe1[0], &cur, sizeof(int)) == 0) 
        exit(0); 

    int child_pipe[2];
    pipe(child_pipe);
    if((pid = fork()) > 0) {
        printf("prime %d\n", cur);
        int i;
        close(child_pipe[0]);
        while(read(pipe1[0], &i, sizeof(int)) != 0) {
            if(i % cur == 0) continue;
            write(child_pipe[1], &i, sizeof(int));
        }
        close(child_pipe[1]);
        wait(0);
    }
    else {
        child(child_pipe); 
    } 
    exit(0);
}

int main(int argc, char *argv[]){ 
    int pid, pipe1[2];
    pipe(pipe1);  
    if((pid = fork()) > 0) {
        close(pipe1[0]);
        for (int i = 2; i <= 35; i++)   
            write(pipe1[1], &i, sizeof(int));
        close(pipe1[1]);  
        wait(0);
    }
    else {
        child(pipe1); 
    } 
    exit(0); 
}

