#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    printf("Parent pid: %d\n\n", getpid());
    
    pid = fork();

    if (pid < 0) {
      fprintf(stderr, "ERROR creating fork!\n");
    } else if (pid == 0) {
      printf("Child pid: %d\n", getpid());
      printf("Parent pid: %d\n", getppid());
      getchar();
    } else {
      getchar();
    }

// $ pstree
//    init(Debian)─┬─SessionLeader───Relay(9)─┬─bash───tmux: client
//             │                          └─tmux: server───2*[bash]
//             ├─SessionLeader───Relay(18)─┬─cpptools-srv───15*[{cpptools-srv}]
//             │                           └─sh───sh───sh───node─┬─node─┬─bash───child───child <- utworzone procesy
//             │                                                 │      ├─bash───pstree
//             │                                                 │      └─12*[{node}]
//             │                                                 ├─node───12*[{node}]
//             │                                                 ├─node─┬─cpptools───17*[{cpptools}]
//             │                                                 │      ├─node───10*[{node}]
//             │                                                 │      └─11*[{node}]
//             │                                                 └─10*[{node}]
//             ├─SessionLeader───Relay(237)───node───6*[{node}]
//             ├─SessionLeader───Relay(253)───node───6*[{node}]
//             ├─init───{init}
//             └─{init(Debian)}

// $ ps axo pid,ppid,command | grep child
//    PID   PPID  COMMAND 
//    4322   414  bin/child
//    4323  4322  bin/child
}
