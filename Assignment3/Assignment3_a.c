#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define BUF_SIZE 1024

int main(void)
{
    char src[256], dest[256];
    int fd_src, fd_dest;
    ssize_t bytes_read, bytes_written;
    char buffer[BUF_SIZE];
    struct stat st;

   
    printf("Enter source file: ");
    fgets(src, sizeof(src), stdin);
    src[strcspn(src, "\n")] = '\0';

    
    printf("Enter destination file: ");
    fgets(dest, sizeof(dest), stdin);
    dest[strcspn(dest, "\n")] = '\0';

    
    fd_src = open(src, O_RDONLY);
    if (fd_src == -1) {
        perror("open source");
        return 1;
    }

    
    if (stat(src, &st) == -1) {
        perror("stat");
        close(fd_src);
        return 1;
    }

    
    fd_dest = open(dest, O_WRONLY | O_CREAT | O_TRUNC, st.st_mode);
    if (fd_dest == -1) {
        perror("open destination");
        close(fd_src);
        return 1;
    }

    
    while ((bytes_read = read(fd_src, buffer, BUF_SIZE)) > 0) {
        bytes_written = write(fd_dest, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("write");
            close(fd_src);
            close(fd_dest);
            return 1;
        }
    }

    if (bytes_read == -1) {
        perror("read");
    }

   
    close(fd_src);
    close(fd_dest);

    printf("File copied successfully.\n");
    return 0;
}
