//Problem statement: copy a file using pread() and pwrite() without changing the offset 
//input: Source and destination file names 
//output: copied file identical to source



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[])
{
    int src_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    off_t offset = 0;
    char buffer[BUF_SIZE];

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Open source file */
    src_fd = open(argv[1], O_RDONLY);
    if (src_fd < 0) {
        perror("open source");
        return EXIT_FAILURE;
    }

    /* Create destination file */
    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (dest_fd < 0) {
        perror("open destination");
        close(src_fd);
        return EXIT_FAILURE;
    }

    /* Copy loop using pread/pwrite */
    while ((bytes_read = pread(src_fd, buffer, BUF_SIZE, offset)) > 0) {

        bytes_written = pwrite(dest_fd, buffer, bytes_read, offset);
        if (bytes_written != bytes_read) {
            perror("pwrite");
            close(src_fd);
            close(dest_fd);
            return EXIT_FAILURE;
        }

        offset += bytes_read;
    }

    if (bytes_read < 0) {
        perror("pread");
        close(src_fd);
        close(dest_fd);
        return EXIT_FAILURE;
    }

    close(src_fd);
    close(dest_fd);

    printf("File copied successfully using pread() and pwrite()\n");
    return EXIT_SUCCESS;
}
