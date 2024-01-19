#include <iostream>
#include <cstdlib>
#include <unistd.h>

void statyczna() {
    double tablica[1000000];

    std::cout << "Funkcja statyczna: Wcisnij Enter, aby kontynuowac... ";
    std::cin.get();
}

void dynamiczna() {
    double *tablica = new double[1000000];
    
    std::cout << "Funkcja dynamiczna: Wcisnij Enter, aby kontynuowac... ";
    std::cin.get();
    
    delete[] tablica;
}

int main() {
    std::cout << getpid() << "\n";

    std::cin.get();

    statyczna();
    
    dynamiczna();
    
    return 0;
}

/*
Start:
           [stack]
Size:                132 kB
KernelPageSize:        4 kB
MMUPageSize:           4 kB
Rss:                  12 kB
Pss:                  12 kB
Pss_Dirty:            12 kB

           [heap]
Size:                132 kB
KernelPageSize:        4 kB
MMUPageSize:           4 kB
Rss:                   8 kB
Pss:                   8 kB
Pss_Dirty:             8 kB

statyczna():
            [stack]
Size:               7824 kB
KernelPageSize:        4 kB
MMUPageSize:           4 kB
Rss:                  16 kB
Pss:                  16 kB
Pss_Dirty:            16 kB

            [heap]
Size:                132 kB
KernelPageSize:        4 kB
MMUPageSize:           4 kB
Rss:                   8 kB
Pss:                   8 kB
Pss_Dirty:             8 kB

statyczna() + dynamiczna():
            [stack]
Size:               7824 kB
KernelPageSize:        4 kB
MMUPageSize:           4 kB
Rss:                  16 kB
Pss:                  16 kB
Pss_Dirty:            16 kB

            [heap]
Size:                132 kB
KernelPageSize:        4 kB
MMUPageSize:           4 kB
Rss:                   8 kB
Pss:                   8 kB
Pss_Dirty:             8 kB
...
Size:               7816 kB
KernelPageSize:        4 kB
MMUPageSize:           4 kB
Rss:                   4 kB
Pss:                   4 kB
Pss_Dirty:             4 kB


Wynik z htop:
2944 kB

Suma z smaps:
3100 kB
*/