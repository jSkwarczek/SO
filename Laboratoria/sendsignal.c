#include <stdint.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if (argc != 3) {
        fprintf(stderr, "ERROR!\n"); 
        return 1;
    }

    pid_t pid = atoi(argv[1]);
    pid_t sig = atoi(argv[2]);
    kill(pid, sig);
    return 0;
}
