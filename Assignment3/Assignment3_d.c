#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void)
{
    char dirname[256];
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    int delete_count = 0;

    
    printf("Enter directory name: ");
    fgets(dirname, sizeof(dirname), stdin);
    dirname[strcspn(dirname, "\n")] = '\0';

    
    dir = opendir(dirname);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {

        
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        char path[512];
        snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);

        
        if (lstat(path, &st) == -1)
            continue;

        
        if (S_ISREG(st.st_mode) && st.st_size == 0) {
            if (unlink(path) == 0) {
                printf("Deleted: %s\n", entry->d_name);
                delete_count++;
            } else {
                perror("unlink");
            }
        }
    }

    closedir(dir);

    printf("\nTotal zero-byte files deleted: %d\n", delete_count);
    return 0;
}
