#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    printf("Parent pid: %d\n\n", getpid());
    
    /* Start children. */
    pid = fork();

    if (pid < 0) {
      fprintf(stderr, "ERROR creating fork!\n");
    } else if (pid == 0) {
      pid = fork();
      printf("Child pid: %d\nParent pid: %d\n", getpid(), getppid());
      getchar;
    } else {
      getchar;
    }

// $ pstree 
//    init(Debian)─┬─SessionLeader───Relay(13)─┬─2*[cpptools-srv───15*[{cpptools-srv}]]
//                 │                           └─sh───sh───sh───node─┬─node─┬─2*[bash]
//                 │                                                 │      ├─bash───grandchild───grandchild───grandchild <- utworzone procesy
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

// $ ps axo pid,ppid,command | grep grandchild
//    PID   PPID  COMMAND 
//    4886   414  bin/grandchild
//    4887  4886  bin/grandchild
//    4888  4887  bin/grandchild
}
