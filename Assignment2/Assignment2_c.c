#include <stdio.h>
#include <dirent.h>
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
        /* Skip "." and ".." */
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}
