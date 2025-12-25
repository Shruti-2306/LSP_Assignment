#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#define BUF_SIZE 4096

/* Copy file contents (used when rename fails with EXDEV) */
int copy_file(const char *src, const char *dest)
{
    int fd_src, fd_dest;
    char buffer[BUF_SIZE];
    ssize_t bytes;
    struct stat st;

    fd_src = open(src, O_RDONLY);
    if (fd_src == -1) {
        perror("open source");
        return -1;
    }

    if (stat(src, &st) == -1) {
        perror("stat");
        close(fd_src);
        return -1;
    }

    fd_dest = open(dest, O_WRONLY | O_CREAT | O_TRUNC, st.st_mode);
    if (fd_dest == -1) {
        perror("open destination");
        close(fd_src);
        return -1;
    }

    while ((bytes = read(fd_src, buffer, BUF_SIZE)) > 0) {
        if (write(fd_dest, buffer, bytes) != bytes) {
            perror("write");
            close(fd_src);
            close(fd_dest);
            return -1;
        }
    }

    if (bytes == -1)
        perror("read");

    close(fd_src);
    close(fd_dest);
    return 0;
}

int main(void)
{
    char src_dir[256], dest_dir[256];
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    int moved_count = 0;

    
    printf("Enter source directory: ");
    fgets(src_dir, sizeof(src_dir), stdin);
    src_dir[strcspn(src_dir, "\n")] = '\0';

    
    printf("Enter destination directory: ");
    fgets(dest_dir, sizeof(dest_dir), stdin);
    dest_dir[strcspn(dest_dir, "\n")] = '\0';

    /* Validate source directory */
    if (stat(src_dir, &st) == -1 || !S_ISDIR(st.st_mode)) {
        printf("Source directory does not exist\n");
        return 1;
    }

    /* Validate destination directory */
    if (stat(dest_dir, &st) == -1 || !S_ISDIR(st.st_mode)) {
        printf("Destination directory does not exist\n");
        return 1;
    }

    dir = opendir(src_dir);
    if (!dir) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {

        /* Skip . and .. */
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        char src_path[512];
        char dest_path[512];

        snprintf(src_path, sizeof(src_path), "%s/%s", src_dir, entry->d_name);
        snprintf(dest_path, sizeof(dest_path), "%s/%s", dest_dir, entry->d_name);

        
        if (lstat(src_path, &st) == -1)
            continue;

        
        if (!S_ISREG(st.st_mode))
            continue;

        
        if (rename(src_path, dest_path) == 0) {
            printf("Moved (rename): %s\n", entry->d_name);
            moved_count++;
        }
        else {
            if (errno == EXDEV) {
                
                if (copy_file(src_path, dest_path) == 0) {
                    unlink(src_path);
                    printf("Moved (copy+delete): %s\n", entry->d_name);
                    moved_count++;
                }
            } else {
                perror("rename");
            }
        }
    }

    closedir(dir);

    printf("\nTotal regular files moved: %d\n", moved_count);
    return 0;
}
