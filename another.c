#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("Hello, I'm an another program! (PID: %d)\n", getpid());
    getchar();
    return 0;
}




























/// Przed execvp():
// tux      10458  0.0  0.0   2460   876 pts/3    S+   13:48   0:00 bin/exec

// Po execvp():
// tux      10458  0.0  0.0   2460   860 pts/3    S+   13:48   0:00 bin/another

// Proces macierzysty bin/exec zostaje zastąpiony przez program potomny bin/another
