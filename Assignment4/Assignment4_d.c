//Problem statment: merge multiple input files into a single output file 
//input: output_file file1 file2 file3 ... 
//output:combined file content in order


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[])
{
    int out_fd, in_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUF_SIZE];
    int i;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <output_file> <input_file1> [input_file2 ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Open output file */
    out_fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (out_fd < 0) {
        perror("open output file");
        return EXIT_FAILURE;
    }

    /* Loop through all input files */
    for (i = 2; i < argc; i++) {

        in_fd = open(argv[i], O_RDONLY);
        if (in_fd < 0) {
            perror(argv[i]);
            close(out_fd);
            return EXIT_FAILURE;
        }

        /* Copy current file into output */
        while ((bytes_read = read(in_fd, buffer, BUF_SIZE)) > 0) {

            bytes_written = write(out_fd, buffer, bytes_read);
            if (bytes_written != bytes_read) {
                perror("write");
                close(in_fd);
                close(out_fd);
                return EXIT_FAILURE;
            }
        }

        if (bytes_read < 0) {
            perror("read");
            close(in_fd);
            close(out_fd);
            return EXIT_FAILURE;
        }

        close(in_fd);
    }

    close(out_fd);

    printf("Files merged successfully into '%s'\n", argv[1]);
    return EXIT_SUCCESS;
}
