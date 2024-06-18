#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

#define MAXLEN 100

int main(int argc, char* argv[])
{
    if (argc <= 1) {
        fprintf(2, "illegal argument number\n");
    }

    char buf;
    char argv_list[MAXARG][MAXLEN];
    char* new_argv_list[MAXARG]; 

    while(1) {
        memset(argv_list, 0, MAXARG * MAXLEN);

        for (int i = 1; i < argc; ++i) {
            strcpy(argv_list[i-1], argv[i]); 
        }

        int cur_argc = argc - 1;
        int offset = 0;
        int is_read = 0;

        while((is_read = read(0, &buf, 1)) > 0) { 
            if (buf == ' ') {
                cur_argc++;
                offset = 0;
                continue;
            }

            if(buf == '\n') {
                break; 
            } 
            argv_list[cur_argc][offset++] = buf;
        }

        if (is_read <= 0) {
            break;
        }

        for (int i = 0; i <= cur_argc; ++i) {
            new_argv_list[i] = argv_list[i];
        }

        if (fork() == 0) {
            exec(argv[1], new_argv_list);
            exit(1);
        }

        wait(0);
    }

    exit(0);
}
