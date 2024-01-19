#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

void error(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(-1);
}

int main(int argc, char *argv[]) {
    if (argc != 4) { error("Invalid number of arguments!"); }

    size_t buffer_size = atoi(argv[1]);
    if (buffer_size == 0) { error("Invalid buffer size!"); }

    char *buffer = malloc(buffer_size);

    if (buffer == NULL) { error("Malloc error!"); }

    FILE *input_file = fopen(argv[2], "rb");
    if (input_file == NULL) {
        free(buffer);
        error("Input file error!");
    }

    FILE *output_file = fopen(argv[3], "wb");
    if (output_file == NULL) {
        fclose(input_file);
        free(buffer);
        error("Output file error!");
    }

    size_t read_bytes, wroted_bytes;

    while ((read_bytes = fread(buffer, 1, buffer_size, input_file)) > 0) {
        wroted_bytes = fwrite(buffer, 1, read_bytes, output_file);
        if (read_bytes != wroted_bytes) { error("Write error!"); }
    }

    fclose(input_file);
    fclose(output_file);
    free(buffer);

    return 0;
}
