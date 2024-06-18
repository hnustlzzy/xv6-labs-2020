#include "kernel/types.h"
#include "user/user.h" 
int main(int argc, char *argv[]){
    if(argc < 2) {
        printf("input error\n");
        exit(0);
    }
    int x = atoi(argv[1]);
    sleep(x);
    exit(0);
}

