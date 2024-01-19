#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sigNum){
    printf("Detected signal number: %d\n", sigNum);
}

int main(void) {
    printf("PID: %d\n", getpid());
    while (1) {
        for (int n = 1; n <= 31; n++) {
            signal(n, handler);
        }
    }
    
    signal(9, handler);
    return 0;
}

