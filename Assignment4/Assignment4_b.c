//Problem Statement: Copy a file starting from a given byte offset of the source file 
//Input: source_file destination_file offset 
//output: partial file copied starting from offset

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[])
{
    int src_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUF_SIZE];
    off_t offset;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file> <offset>\n", argv[0]);
        return EXIT_FAILURE;
    }

    offset = atoll(argv[3]);
    if (offset < 0) {
        fprintf(stderr, "Offset must be non-negative\n");
        return EXIT_FAILURE;
    }

    src_fd = open(argv[1], O_RDONLY);
    if (src_fd < 0) {
        perror("open source file");
        return EXIT_FAILURE;
    }

    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("open destination file");
        close(src_fd);
        return EXIT_FAILURE;
    }

    if (lseek(src_fd, offset, SEEK_SET) == (off_t)-1) {
        perror("lseek");
        close(src_fd);
        close(dest_fd);
        return EXIT_FAILURE;
    }

    while ((bytes_read = read(src_fd, buffer, BUF_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("write");
            close(src_fd);
            close(dest_fd);
            return EXIT_FAILURE;
        }
    }

    if (bytes_read < 0) {
        perror("read");
        close(src_fd);
        close(dest_fd);
        return EXIT_FAILURE;
    }

    close(src_fd);
    close(dest_fd);

    
    printf("File copied successfully from offset %lld bytes.\n",
           (long long)offset);

    return EXIT_SUCCESS;
}
