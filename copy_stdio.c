/*
 * Practical Session 9 (Part 2): Standard C Library File Copy
 * Uses fopen(), fread(), fwrite(), and fseek()/ftell() to copy files and calculate size.
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 8192

int main(int argc, char *argv[]) {
    FILE *src;
    FILE *dest;
    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    /* Open source file in binary read mode */
    src = fopen(argv[1], "rb");
    if (src == NULL) {
        perror("fopen source");
        return 1;
    }

    /* Open/create destination file in binary write mode */
    dest = fopen(argv[2], "wb");
    if (dest == NULL) {
        perror("fopen destination");
        fclose(src);
        return 1;
    }

    /* Copy file */
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
        size_t total_written = 0;
        while (total_written < bytes_read) {
            size_t bytes_written = fwrite(buffer + total_written, 1, bytes_read - total_written, dest);
            if (bytes_written == 0) {
                if (ferror(dest)) {
                    perror("fwrite");
                    fclose(src);
                    fclose(dest);
                    return 1;
                }
            }
            total_written += bytes_written;
        }
    }

    if (ferror(src)) {
        perror("fread");
        fclose(src);
        fclose(dest);
        return 1;
    }

    /* Determine file size using fseek() and ftell() */
    if (fseek(src, 0, SEEK_END) == 0) {
        long file_size = ftell(src);
        if (file_size >= 0) {
            printf("Source file size (via fseek/ftell): %ld bytes\n", file_size);
        }
    }

    fclose(src);
    fclose(dest);
    printf("File copied successfully via standard library streams.\n");
    return 0;
}
