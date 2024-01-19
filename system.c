#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    printf("Hello, I'm system program! (PID %d)\n", getpid());
    getchar();
    system("sleep 60");
    getchar();
    return 0;
}

// Przed wykonaniem system()
//tux        51849  0.0  0.0   2660  1536 pts/0    S+   23:32   0:00 ./bin/system

// Po wykonaniu system()
//tux        51849  0.0  0.0   2660  1536 pts/0    S+   23:32   0:00 ./bin/system
//tux        51889  0.0  0.0   2780  1792 pts/0    S+   23:33   0:00 sh -c -- sleep 60
//tux        51890  0.0  0.0   5608  2176 pts/0    S+   23:33   0:00 sleep 60

// Po zakończeniu procesu stworzonego przez system()
//tux        51849  0.0  0.0   2660  1536 pts/0    S+   23:32   0:00 ./bin/system


// Funkcja system() tworzy nowy proces, a następnie po jego wykonaniu następuje powrót do procesu rodzica i dalsza egzekucja. 