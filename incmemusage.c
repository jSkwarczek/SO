#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INITIAL_SIZE 1000
#define GROWTH_FACTOR 2

int wait() {
    printf("Press Enter to continue...");
    int i;
    scanf("%d", &i);
    if (i == 1) { return 1; }
    return 0;
}

int main() {
    printf("%d\n", getpid());

    double*** array2D = (double***)malloc(INITIAL_SIZE * sizeof(double**));
    if (array2D == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return -1;
    }

    (void)wait();

    int size = INITIAL_SIZE;

    while (1) {
        size *= GROWTH_FACTOR;

        array2D = (double***)realloc(array2D, size * sizeof(double**));
        if (array2D == NULL) {
            fprintf(stderr, "Memory reallocation failed.\n");
            return -1;
        }
        
        memset(array2D, 0, size * sizeof(double**));

        printf("Memory reallocated for %d elements.\n", size);

        if (wait()) { break; }
    }

    for (int i = 0; i < size; i++) {
        free(array2D[i]);
    }
    free(array2D);

    return 0;
}

/*
Zajętość pamięci głównej i wirtualnej rośnie do momentu, aż proces zostanie zakończony przez system.
*/