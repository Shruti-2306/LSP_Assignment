//problem statement: directory traversal basics 
//create a program ls.clone.c that takes one directory path and prints: 
//entry name type(file/dir/link other) 
//size(bytes) 
//permissions in rwxr-xr-r format 
//Last modified time 
//skip . and .. build full path using snprintf(dir + "/" + name)


#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>   // mode_t
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>      // PATH_MAX

void print_permissions(mode_t mode)
{
    char perm[10];

    perm[0] = (mode & S_IRUSR) ? 'r' : '-';
    perm[1] = (mode & S_IWUSR) ? 'w' : '-';
    perm[2] = (mode & S_IXUSR) ? 'x' : '-';

    perm[3] = (mode & S_IRGRP) ? 'r' : '-';
    perm[4] = (mode & S_IWGRP) ? 'w' : '-';
    perm[5] = (mode & S_IXGRP) ? 'x' : '-';

    perm[6] = (mode & S_IROTH) ? 'r' : '-';
    perm[7] = (mode & S_IWOTH) ? 'w' : '-';
    perm[8] = (mode & S_IXOTH) ? 'x' : '-';

    perm[9] = '\0';
    printf("%s", perm);
}

const char *get_type(mode_t mode)
{
    if (S_ISREG(mode)) return "file";
    if (S_ISDIR(mode)) return "dir";
    if (S_ISLNK(mode)) return "link";
    return "other";
}

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *de;
    struct stat st;
    char fullpath[PATH_MAX];
    char timebuf[64];
    struct tm *tm_info;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    dp = opendir(argv[1]);
    if (!dp) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    while ((de = readdir(dp)) != NULL) {

        if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
            continue;

        snprintf(fullpath, sizeof(fullpath),
                 "%s/%s", argv[1], de->d_name);

        if (lstat(fullpath, &st) == -1) {
            perror("lstat");
            continue;
        }

        tm_info = localtime(&st.st_mtime);
        if (!tm_info)
            continue;

        strftime(timebuf, sizeof(timebuf),
                 "%Y-%m-%d %H:%M:%S", tm_info);

        printf("%-20s ", de->d_name);
        printf("%-6s ", get_type(st.st_mode));
        printf("%8lld ", (long long)st.st_size);
        print_permissions(st.st_mode);
        printf(" %s\n", timebuf);
    }

    closedir(dp);
    return EXIT_SUCCESS;
}
