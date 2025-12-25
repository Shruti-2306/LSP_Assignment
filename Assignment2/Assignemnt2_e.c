#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include<sys/types.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    char dirname[256];
    DIR *dir;
    struct dirent *entry;

    printf("Enter directory name: ");
    if (fgets(dirname, sizeof(dirname), stdin) == NULL) {
        perror("fgets");
        return 1;
    }
    dirname[strcspn(dirname, "\n")] = '\0';  // remove newline

    dir = opendir(dirname);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    char largest_file[256] = "";
    
    off_t largest_size = 0;

    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        
        char path[512];
        snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);

        struct stat st;
        if (lstat(path, &st) == -1) {
            perror("lstat");
            continue;
        }

        
        if (S_ISREG(st.st_mode)) {
            if (st.st_size > largest_size) {
                largest_size = st.st_size;
                strcpy(largest_file, entry->d_name);
            }
        }
    }

    closedir(dir);

    if (largest_size > 0)
        printf("Largest file: %s\nSize: %ld bytes\n", largest_file, largest_size);
    else
        printf("No regular files found in directory.\n");

    return 0;
}
