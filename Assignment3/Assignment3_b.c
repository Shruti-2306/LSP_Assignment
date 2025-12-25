#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    char dirname[256];
    char filename[256];
    DIR *dir;
    struct dirent *entry;

    printf("Enter directory name: ");
    fgets(dirname, sizeof(dirname), stdin);
    dirname[strcspn(dirname, "\n")] = '\0';

    printf("Enter file name to search: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    dir = opendir(dirname);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    char *abs_dir = realpath(dirname, NULL);
    if (abs_dir == NULL) {
        perror("realpath");
        closedir(dir);
        return 1;
    }

    int found = 0;

    while ((entry = readdir(dir)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        if (strcmp(entry->d_name, filename) == 0) {
            printf("File found!\n");
            printf("Absolute path: %s/%s\n", abs_dir, filename);
            found = 1;
            break;
        }
    }

    free(abs_dir);
    closedir(dir);

    if (!found)
        printf("File not found in directory.\n");

    return 0;
}
