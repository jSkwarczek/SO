#include <unistd.h>
#include <stdio.h>

int main(void) {
    printf("Hello, I'm exec program! (PID: %d)\n", getpid());
    getchar();

    char *args[] = {"bin/another", NULL};
    execvp(args[0], args);
    return 0;
}

// Przed execvp():
// tux      10458  0.0  0.0   2460   876 pts/3    S+   13:48   0:00 bin/exec

// Po execvp():
// tux      10458  0.0  0.0   2460   860 pts/3    S+   13:48   0:00 bin/another

// Proces macierzysty bin/exec zostaje zastąpiony przez program potomny bin/another
