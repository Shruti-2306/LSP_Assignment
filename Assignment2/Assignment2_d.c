#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

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
   dirname[strcspn(dirname, "\n")] = '\0';

    dir = opendir(dirname);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    printf("\nDirectory contents:\n");

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        
        char path[512];
        snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);

        struct stat st;
        if (lstat(path, &st) == -1) {
            perror("lstat");
            continue;
        }

        
        char *type;
        if (S_ISREG(st.st_mode))
            type = "regular";
        else if (S_ISDIR(st.st_mode))
            type = "directory";
        else if (S_ISLNK(st.st_mode))
            type = "link";
        else if (S_ISFIFO(st.st_mode))
            type = "fifo";
        else if (S_ISSOCK(st.st_mode))
            type = "socket";
        else if (S_ISCHR(st.st_mode))
            type = "char";
        else if (S_ISBLK(st.st_mode))
            type = "block";
        else
            type = "unknown";

        printf("%s\t%s\n", entry->d_name, type);
    }

    closedir(dir);
    return 0;
}
