#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pids[2];
    pid_t pid;

    printf("Parent pid: %d\n\n", getpid());
    
    /* Start children. */
    for (int n = 0; n<2; n++){
      pids[n] = fork();
      
      if (pids[n] < 0) {
        fprintf(stderr, "ERROR creating fork!\n");
      } else if (pids[n] == 0) {
        if (n == 0) { pid = fork(); }
        printf("Child pid: %d\nParent pid: %d\n", getpid(), getppid());
        getchar();
        break;
      }
    }

    getchar();

















// $ pstree
//    init(Debian)─┬─SessionLeader───Relay(13)─┬─2*[cpptools-srv───15*[{cpptools-srv}]]
//                 │                           └─sh───sh───sh───node─┬─node─┬─2*[bash]
//                 │                                                 │      ├─bash───brother─┬─brother───brother  <-┬- utworzone procesy
//                 │                                                 │      │                └─brother  <-----------┘
//                 │                                                 │      └─13*[{node}]
//                 │                                                 ├─node───12*[{node}]
//                 │                                                 ├─node─┬─cpptools───17*[{cpptools}]
//                 │                                                 │      ├─node───10*[{node}]
//                 │                                                 │      ├─node───6*[{node}]
//                 │                                                 │      └─11*[{node}]
//                 │                                                 └─10*[{node}]
//                 ├─SessionLeader───Relay(36)───node───6*[{node}]
//                 ├─SessionLeader───Relay(70)───node───6*[{node}]
//                 ├─SessionLeader───Relay(5142)───bash───pstree
//                 ├─init───{init}
//                 └─{init(Debian)}

// $ ps axo pid,ppid,command | grep brother
//    PID   PPID  COMMAND 
//    5652   414  bin/brother
//    5653  5652  bin/brother
//    5654  5652  bin/brother
//    5655  5653  bin/brother
}
