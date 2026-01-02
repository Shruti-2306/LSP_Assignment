//Problem statement : display the contents of a file in reverse order 
//input: file name 
//output: file content printed in reverse

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;
    off_t size;
    char ch;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }

    /* Get file size */
    size = lseek(fd, 0, SEEK_END);
    if (size == (off_t)-1) {
        perror("lseek");
        close(fd);
        return EXIT_FAILURE;
    }

    /* Read file in reverse */
    for (off_t i = size - 1; i >= 0; i--) {

        if (lseek(fd, i, SEEK_SET) == (off_t)-1) {
            perror("lseek");
            close(fd);
            return EXIT_FAILURE;
        }

        if (read(fd, &ch, 1) != 1) {
            perror("read");
            close(fd);
            return EXIT_FAILURE;
        }

        write(STDOUT_FILENO, &ch, 1);
    }
    printf("\n");
    close(fd);
    return EXIT_SUCCESS;
}
