#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE (4096U)

int fileCopy(const char * const src, const char * const dest);

int main(void) {
    if (fileCopy("test.log", "test42.log") != 0) {
        perror("fileCopy");
        exit(EXIT_FAILURE);
    }

    return 0;
}

void dummy() {
    FILE *file = fopen("test.txt", "r+");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    int i;
    fscanf(file, "%d", &i);

    char buffer[BUFFER_SIZE];
    size_t count = fread(buffer, 1, BUFFER_SIZE, file);
    if (ferror(file) != 0) {
        perror("fread");
        exit(EXIT_FAILURE);
    }

    printf("count: %zu\n", count);
    for (size_t i = 0; i < count; ++i) {
        printf("%zu: %d\n", i, buffer[i]);
    }

    if (fseek(file, -7, SEEK_END) != 0) {
        perror("fseek");
        exit(EXIT_FAILURE);
    }

    long tell = ftell(file);
    if (tell == -1) {
        perror("ftell");
        exit(EXIT_FAILURE);
    }

    printf("tell: %ld\n", tell);

    printf("i = %d\n", i);
    fprintf(file, "Hello %s %d\n", "MAI", i * 3 + 1);

    if (fclose(file) == EOF) {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
    rename("test.txt", "test.log");
}

int fileCopy(const char * const src, const char * const dest) {
    FILE * const srcFile = fopen(src, "r");
    if (srcFile == NULL)
        return errno;

    FILE * const destFile = fopen(dest, "w");
    if (destFile == NULL) {
        const int err = errno;
        fclose(srcFile);
        errno = err;
        return errno;
    }

    char buffer[BUFFER_SIZE];
    size_t count;
    do {
        count = fread(buffer, sizeof buffer[0], BUFFER_SIZE, srcFile);
        if (ferror(srcFile)) {
            const int err = errno;
            fclose(srcFile);
            fclose(destFile);
            errno = err;
            return errno;
        }
        fwrite(buffer, sizeof buffer[0], count, destFile);
        if (ferror(destFile)) {
            const int err = errno;
            fclose(srcFile);
            fclose(destFile);
            errno = err;
            return errno;
        }
    } while (feof(srcFile) == 0);

    if (fclose(srcFile) == EOF)
        return errno;
    if (fclose(destFile) == EOF)
        return errno;
    return 0;
}
